#include <cstdio>

void matrix_sort(char matrix[5][5]) {
    int row_len = 5;
    int last = row_len * row_len;
    char temp;

//    for (int i = 0; i < last; i++) {
//        for (int j = 0; j < last - i - 1; j++) {
//
//            if (*(*matrix+j) > *(*matrix+j+ 1)) {
//                // меняем элементы местами
//                temp = *(*matrix+j);
//                *matrix+j = *matrix+(j+1);
//                arr[j + 1] = temp;
//            }
//        }
//    }
    for(int i=0; i<last ;i++) {
        int row_index = i / row_len;
        int col_index = i % row_len;

        for (int j = i; j < last; j++) {
            int row_index_2 = j / row_len;
            int col_index_2 = j % row_len;

            if (matrix[row_index][col_index] > matrix[row_index_2][col_index_2]) {
                temp = matrix[row_index][col_index];
                matrix[row_index][col_index] = matrix[row_index_2][col_index_2];
                matrix[row_index_2][col_index_2] = temp;
            }
        }
    }
}

int main() {
    char matrix[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = j+i*5;
            printf("%c ", 'z' - index);
            matrix[i][j] = static_cast<char>('z' - index);
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {

            printf("%c ", matrix[i][j]);
        }
    }

    matrix_sort(matrix);

    printf("\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {

            printf("%c ", matrix[i][j]);
        }
    }
}