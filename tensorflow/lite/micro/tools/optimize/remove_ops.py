import os
from absl import app
from absl import flags


FLAGS = flags.FLAGS
flags.DEFINE_string(
    'prj_dir', None,
    'Path to the project direcotry to optimize.'
    'This is typically the top level directory'
)

flags.mark_flag_as_required('prj_dir')


SKIP_FILES=["lite/core/c/common.cc", "detection_postprocess.cc", "kernels/l2_pool_2d.cc", "kernels/neg.cc", 'mul.cc']

def remove_case_with_bracket(content, file_path, kTFLiteType="kTfLiteFloat32"):    
    M = []
    processing = False

    for line in content:
        if f"case {kTFLiteType}: {{" in line:        
            print(f'Removing {kTFLiteType} from {file_path}')            
            queue = 1
            processing=True
            continue
        
        if processing:
            queue += line.count('{')
            queue -= line.count('}')
            if queue == 0:
                processing=False
                continue
            
        if not processing:
            M.append(line)

    return M


def remove_case(content, file_path, kTFLiteType="kTfLiteFloat32"):    
    M = []
    processing = False

    for line in content:
        if f"case {kTFLiteType}:" in line:        
            print(f'Removing {kTFLiteType} from {file_path}')            
            processing=True
            continue
        
        if processing:
            if "case kTfLite" in line or "default:" in line:
                processing=False            
            
        if not processing:
            M.append(line)

    return M

def replace_keyword_in_files(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            if any([x in file_path for x in SKIP_FILES]):
                print("SKIPPED", file_path)
                continue
            with open(file_path, 'r') as f:
                content = f.readlines()
            
            replaced_content = remove_case(content, file_path)
            replaced_content = remove_case_with_bracket(replaced_content, file_path)
            
            
            with open(file_path, 'w') as f:
                f.write("".join(replaced_content))



def main(_):
    
  prj_dir = FLAGS.prj_dir
  
  replace_keyword_in_files(prj_dir)  
  
if __name__ == '__main__':
  app.run(main)
