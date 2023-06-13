import re
import binascii
import json
import os
from absl import app
from absl import flags
import shutil


FLAGS = flags.FLAGS
flags.DEFINE_string(
    'model_path', None,
    'Path tflite model file.'
    ''
)

flags.DEFINE_string(
    'model_binary', None,
    'Model binary'
    ''
)

flags.DEFINE_string(
    'model_json_path', None,
    'Path to the model_json file'
    'The model json file must contain "model_binary" and may contain "test_data", see example test_model.json'
)

def parse_model_file(path, variable_name='g_model'):
    """this will parse the hex string form a model file model_data[] = {0x18, 0x00, ....} given
    the file path and the variable name
    """
    M = []
    with open(path, "r") as fid:
        start_parsing = False
        for line in fid.readlines():
            if start_parsing:
                M.append(line.lstrip())
            if variable_name in line:
                start_parsing = True
            if "};" in line:
                start_parsing = False

    return parse_model_hex_string("".join(M).replace("};", ""))


def parse_model_hex_string(hex_string):
    """this will parse the hex string form a model file
        only pass in the string with the hex values  '0x18, 0x00...
    '"""
    hex_string.replace(",\n", "")
    return "".join([x.lstrip().rstrip()[2:4] for x in hex_string.split(",")])


def to_c_hex(tflite_model):
    hex_str = binascii.hexlify(tflite_model).decode()
    return (
        "".join(
            ["0x{}, ".format(hex_str[i : i + 2]) for i in range(0, len(hex_str), 2)]
        )[:-2],
        len(hex_str) // 2,
    )


def fill_model_template_file(
    model,
    template_path="./model.cc.tpl",
    output="../model.cc",
):

    model_str, model_length = to_c_hex(binascii.unhexlify(model))
    template = {
        "MODEL": f"const unsigned char g_model[] DATA_ALIGN_ATTRIBUTE = {{{model_str}}};",
        "MODEL_LENGTH": f"const int g_model_len = {model_length};",
    }

    with open(template_path, "r") as fid:
        output_str = "".join(fid.readlines())
        for key, value in template.items():
            output_str = re.sub(
                r"//FILL_{}\b".format(key.upper()),
                value,
                output_str,
            )

    with open(output, "w") as out:
        out.write(output_str)

    return template


def fill_test_data(
    test_data,
    output="../test_data.h",
):
    import random

    test_data = [[random.randint(0, 200) for _ in range(23*49)]]

    num_inputs = len(test_data[0])
    num_outputs = 3
    outputs = []
    outputs.append("#include <stdint.h>")
    outputs.append(f"#define MODEL_INPUTS {num_inputs}")
    outputs.append(f"#define MODEL_OUTPUTS {num_outputs}")
    outputs.append(
        "float results[MODEL_OUTPUTS] ={{ {} }};".format(
            ", ".join(["0" for _ in range(num_outputs)])
        )
    )

    outputs.append("uint8_t test_data[MODEL_INPUTS] = ")

    for i in range(len(test_data)):
        outputs.append("{{ {} }};".format(", ".join([str(x) for x in test_data[i]])))


    with open(output, "w") as out:
        out.write("\n".join(outputs))

    return "\n".join(outputs)


def main(_):

    model_path = FLAGS.model_path
    model_binary = FLAGS.model_binary
    model_json_path = FLAGS.model_json_path


    if model_path or model_binary or model_json_path:
        if model_path:
            model = parse_model_file(model_path)
        elif model_binary:
            model = model_binary
        elif model_json_path:
            model_json = json.load(open(model_json_path, "r"))
            model = model_json['model_binary']
            if model_json.get('test_data'):
                print("Generate test_data.h")
                fill_test_data(model_json.get('test_data'))
            
        with open("model.tflite", "wb") as out:
            out.write(binascii.unhexlify(model))

        print("Generate model.cc")
        fill_model_template_file(model)

    else:
        shutil.copy('./all_micro_mutable_op_resolver.h', '../../../gen_micro_mutable_op_resolver.h')
    

    shutil.copy('./micro_api.cc', '../../../micro_api.cc')
    shutil.copy('./micro_api.h', '../../../micro_api.h')


if __name__ == '__main__':
  app.run(main)
