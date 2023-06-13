#include <stdint.h>
#define MODEL_INPUTS 1127
#define MODEL_OUTPUTS 3
float results[MODEL_OUTPUTS] ={ 0, 0, 0 };
uint8_t test_data[MODEL_INPUTS] = 
{ 11, 65, 55, 170, 17, 131, 96, 107, 14, 92, 79, 52, 99, 16, 198, 22, 75, 146, 159, 16, 77, 40, 0, 108, 118, 150, 98, 68, 22, 200, 142, 192, 124, 141, 58, 107, 168, 10, 152, 151, 183, 6, 194, 120, 192, 183, 111, 106, 140, 85, 5, 75, 138, 70, 24, 178, 81, 200, 146, 57, 106, 52, 199, 22, 78, 123, 104, 22, 2, 13, 120, 69, 164, 118, 126, 38, 199, 46, 182, 2, 176, 121, 161, 132, 147, 187, 99, 138, 71, 132, 101, 101, 25, 37, 153, 172, 164, 50, 109, 22, 182, 117, 21, 171, 75, 25, 37, 156, 66, 86, 134, 30, 43, 30, 157, 99, 180, 94, 189, 200, 93, 132, 154, 177, 128, 65, 6, 56, 67, 164, 45, 174, 19, 109, 185, 129, 160, 69, 151, 44, 70, 169, 96, 62, 193, 69, 3, 70, 196, 2, 33, 155, 3, 28, 95, 11, 68, 131, 127, 105, 48, 137, 103, 103, 99, 99, 137, 198, 74, 193, 16, 84, 160, 137, 176, 2, 35, 141, 108, 175, 172, 163, 77, 155, 141, 172, 21, 26, 48, 8, 199, 97, 165, 108, 200, 56, 65, 61, 163, 142, 194, 135, 159, 167, 23, 82, 19, 122, 165, 6, 2, 131, 18, 53, 67, 86, 21, 107, 12, 37, 136, 160, 133, 98, 168, 88, 19, 144, 103, 165, 11, 160, 55, 119, 198, 158, 98, 132, 196, 81, 192, 101, 15, 53, 151, 111, 40, 32, 160, 129, 6, 117, 168, 106, 155, 168, 22, 49, 17, 166, 54, 51, 112, 10, 173, 115, 122, 39, 187, 101, 114, 47, 6, 159, 48, 145, 50, 74, 128, 2, 5, 188, 27, 81, 28, 44, 145, 13, 95, 43, 184, 147, 193, 198, 171, 22, 102, 183, 64, 159, 57, 132, 116, 52, 33, 81, 166, 164, 1, 121, 143, 4, 200, 56, 114, 180, 55, 61, 179, 124, 99, 18, 183, 81, 117, 40, 176, 172, 91, 151, 189, 186, 125, 165, 19, 17, 131, 112, 158, 13, 73, 191, 104, 20, 196, 178, 63, 135, 113, 192, 64, 174, 52, 8, 8, 186, 102, 131, 134, 198, 157, 192, 139, 28, 181, 115, 151, 52, 67, 38, 31, 174, 65, 161, 95, 74, 194, 88, 98, 170, 119, 89, 74, 180, 30, 85, 26, 194, 13, 12, 10, 187, 150, 144, 139, 196, 86, 76, 42, 109, 148, 46, 132, 15, 42, 39, 186, 43, 159, 2, 113, 116, 13, 124, 123, 91, 17, 69, 75, 135, 70, 80, 125, 11, 29, 169, 64, 61, 172, 121, 121, 48, 152, 179, 182, 67, 11, 144, 6, 125, 142, 47, 84, 82, 20, 47, 176, 192, 148, 55, 110, 131, 142, 163, 160, 110, 166, 0, 21, 143, 141, 138, 76, 126, 199, 13, 147, 60, 61, 163, 100, 47, 131, 186, 118, 128, 164, 112, 42, 84, 55, 57, 167, 144, 151, 184, 118, 140, 13, 135, 33, 51, 139, 177, 115, 124, 40, 55, 91, 93, 109, 56, 198, 54, 3, 52, 197, 124, 116, 112, 108, 84, 172, 11, 110, 34, 137, 190, 184, 199, 32, 175, 49, 19, 0, 110, 112, 128, 168, 59, 168, 94, 59, 45, 53, 195, 125, 139, 157, 120, 155, 194, 145, 30, 39, 61, 64, 192, 108, 134, 126, 148, 99, 36, 172, 121, 167, 98, 173, 23, 177, 125, 76, 124, 112, 149, 40, 68, 36, 134, 158, 72, 196, 17, 42, 56, 189, 55, 168, 124, 124, 152, 116, 73, 98, 198, 95, 192, 173, 38, 127, 65, 178, 153, 128, 22, 195, 85, 186, 171, 71, 80, 130, 192, 117, 155, 108, 118, 128, 7, 8, 151, 112, 102, 69, 178, 3, 30, 156, 65, 185, 166, 39, 130, 18, 53, 63, 19, 89, 181, 149, 181, 151, 169, 172, 31, 155, 25, 193, 104, 57, 38, 152, 58, 68, 81, 120, 60, 51, 109, 34, 111, 164, 123, 65, 197, 200, 2, 3, 187, 198, 104, 136, 94, 114, 84, 113, 154, 73, 13, 128, 70, 27, 167, 190, 171, 181, 84, 156, 119, 121, 171, 188, 131, 161, 13, 45, 54, 188, 40, 53, 93, 72, 56, 9, 93, 106, 91, 93, 192, 62, 127, 109, 34, 166, 23, 175, 136, 2, 1, 56, 3, 10, 39, 200, 20, 18, 193, 30, 118, 199, 170, 21, 125, 25, 153, 101, 8, 92, 58, 83, 170, 43, 81, 56, 88, 138, 79, 13, 127, 52, 28, 191, 64, 50, 129, 107, 114, 43, 28, 17, 101, 140, 4, 2, 126, 0, 78, 12, 34, 52, 30, 84, 155, 176, 18, 45, 143, 46, 82, 40, 99, 162, 119, 97, 18, 55, 162, 89, 132, 196, 177, 159, 115, 114, 197, 181, 61, 121, 111, 144, 188, 163, 63, 138, 166, 187, 25, 21, 35, 55, 52, 21, 35, 159, 152, 183, 197, 31, 167, 81, 135, 6, 121, 169, 192, 138, 75, 0, 116, 53, 84, 98, 49, 169, 85, 166, 65, 28, 200, 198, 76, 10, 58, 127, 145, 59, 175, 41, 36, 147, 93, 113, 148, 12, 151, 35, 196, 100, 81, 31, 89, 196, 129, 179, 4, 93, 127, 13, 197, 87, 112, 184, 78, 114, 92, 59, 92, 174, 58, 130, 114, 199, 193, 66, 194, 95, 120, 74, 173, 160, 24, 85, 194, 197, 195, 163, 88, 88, 171, 161, 70, 76, 15, 152, 5, 30, 170, 128, 165, 193, 190, 116, 129, 103, 195, 127, 68, 126, 152, 129, 4, 7, 47, 70, 113, 9, 84, 48, 57, 41, 136, 107, 83, 39, 162, 148, 34, 170, 107, 194, 0, 99, 166, 10, 27, 20, 158, 176, 39, 159, 199, 60, 31, 87, 28, 176, 189, 91, 122, 193, 134, 113, 122, 176, 172, 137, 128, 113, 79, 159, 102, 65, 47, 86, 89, 33, 130, 11, 14, 24, 82, 43, 129, 12, 35, 184, 59, 131, 113, 109, 94, 58, 154, 82, 6, 63, 198, 61, 189, 53, 136, 133, 119, 171, 138, 84, 152, 180, 23, 87, 77, 46, 155, 104, 87, 152, 99, 198, 85, 79, 0, 122, 56, 169, 167, 11, 164, 76, 5, 62, 89, 54, 147, 182, 132, 127, 33, 69, 181, 123, 33, 132, 56, 185, 159, 184, 163, 100, 28, 89, 46, 147, 157, 142, 11, 83, 80, 199, 135, 199, 156, 125, 68, 47, 133, 149, 149, 120, 56, 6, 169, 55, 197, 187, 57, 145, 32, 150, 103, 151, 1, 81, 72, 130, 148, 197, 184, 26, 96, 165, 31, 4, 15, 172, 157, 124, 114, 138, 48, 168, 150, 146, 121, 151, 153, 14, 127, 1, 74, 34, 119, 36, 1, 143, 107, 41, 147, 16, 192, 52, 86, 89, 146, 182, 130, 56, 40, 165, 64, 41, 109, 186, 5, 158, 142, 86 };