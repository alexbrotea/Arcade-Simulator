/* Copyright 2024 Florin-Alexandru Brotea */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int task;
    scanf("%d", &task);

    if (task == 1) {
        int n, m, c, r;
        scanf("%d %d", &n, &m);

        int **mat = malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            mat[i] = malloc(m * sizeof(int));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        scanf("%d %d", &c, &r);

        int *tmp = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            tmp[(i + r) % n] = mat[i][c];
        }
        for (int i = 0; i < n; i++) {
            mat[i][c] = tmp[i];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }

        free(tmp);
        for (int i = 0; i < n; i++) {
            free(mat[i]);
        }
        free(mat);
    }

    if (task == 2) {
        int n, m;
        scanf("%d %d", &n, &m);

        int **mat = malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            mat[i] = malloc(m * sizeof(int));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        int nr_comb = 0, score = 0, nr_sym = 0;
        int *dist = calloc(10, sizeof(int));

        int max_rows = (n < 3) ? n : 3;

        for (int i = 0; i < max_rows; i++) {
            int max_secv_len = 1, curr_secv_len = 1;
            int seq_symbol = mat[i][0];

            for (int j = 1; j < m; j++) {
                if (mat[i][j] == mat[i][j - 1]) {
                    curr_secv_len++;
                } else {
                    curr_secv_len = 1;
                }
                if (curr_secv_len > max_secv_len) {
                    max_secv_len = curr_secv_len;
                    seq_symbol = mat[i][j];
                }
            }

            if (max_secv_len >= 3) {
                nr_comb++;
                int line_score = max_secv_len;
                if (seq_symbol == 7) {
                    line_score *= 2;
                }
                score += line_score;
            }
        }

        int max_cols = m - 2;
        if (max_cols > 0 && n >= 3) {
            for (int j = 0; j < max_cols; j++) {
                bool diag1 = false, diag2 = false;
                int center_symbol = mat[1][j + 1];

                if (mat[0][j] == center_symbol &&
                center_symbol == mat[2][j + 2]) {
                    diag1 = true;
                }

                if (mat[2][j] == center_symbol &&
                center_symbol == mat[0][j + 2]) {
                    diag2 = true;
                }

                if (diag1 && diag2) {
                    nr_comb++;
                    int diag_score = 21;
                    if (center_symbol == 7) {
                        diag_score *= 2;
                    }
                    score += diag_score;
                } else {
                    if (diag1) {
                        nr_comb++;
                        int diag_score = 7;
                        if (center_symbol == 7) {
                            diag_score *= 2;
                        }
                        score += diag_score;
                    }
                    if (diag2) {
                        nr_comb++;
                        int diag_score = 7;
                        if (center_symbol == 7) {
                            diag_score *= 2;
                        }
                        score += diag_score;
                    }
                }
            }
        }

        for (int i = 0; i < max_rows; i++) {
            for (int j = 0; j < m; j++) {
                int sym = mat[i][j];
                if (sym >= 0 && sym <= 9 && dist[sym] == 0) {
                    dist[sym] = 1;
                    nr_sym++;
                }
            }
        }

        if (nr_sym <= 2) {
            score += 100;
        } else if (nr_sym <= 4) {
            score += 15;
        }

        printf("%d\n", nr_comb);
        printf("%d\n", score);

        free(dist);
        for (int i = 0; i < n; i++) {
            free(mat[i]);
        }
        free(mat);
    }

    if (task == 4) {
        int n, m;
        scanf("%d %d", &n, &m);

        int **mat = malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            mat[i] = malloc(m * sizeof(int));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        int max_score = 0;
        int max_sym = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] > max_sym) {
                    max_sym = mat[i][j];
                }
            }
        }

        int max_possible_sym = max_sym + 1;

        int **new_mat = malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            new_mat[i] = malloc(m * sizeof(int));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int init_sym = mat[i][j];

                for (int new_sym = 0; new_sym <= max_possible_sym; new_sym++) {
                    if (new_sym == init_sym) {
                        continue;
                    }

                    for (int k = 0; k < n; k++) {
                        for (int l = 0; l < m; l++) {
                            new_mat[k][l] = mat[k][l];
                        }
                    }
                    new_mat[i][j] = new_sym;

                    int temp_score = 0, nr_comb = 0, nr_sym = 0;
                    int *dist = calloc(max_sym + 2, sizeof(int));

                    int max_rows = (n < 3) ? n : 3;

                    for (int row = 0; row < max_rows; row++) {
                        int max_secv_len = 1, curr_secv_len = 1;
                        int seq_symbol = new_mat[row][0];

                        for (int col = 1; col < m; col++) {
                            if (new_mat[row][col] == new_mat[row][col - 1]) {
                                curr_secv_len++;
                            } else {
                                curr_secv_len = 1;
                            }
                            if (curr_secv_len > max_secv_len) {
                                max_secv_len = curr_secv_len;
                                seq_symbol = new_mat[row][col];
                            }
                        }

                        if (max_secv_len >= 3) {
                            nr_comb++;
                            int line_score = max_secv_len;
                            if (seq_symbol == 7) {
                                line_score *= 2;
                            }
                            temp_score += line_score;
                        }
                    }

                    int max_cols = m - 2;
                    if (max_cols > 0 && n >= 3) {
                        for (int col = 0; col < max_cols; col++) {
                            bool diag1 = false, diag2 = false;
                            int center_symbol = new_mat[1][col + 1];

                            if (new_mat[0][col] == center_symbol &&
                            center_symbol == new_mat[2][col + 2]) {
                                diag1 = true;
                            }

                            if (new_mat[2][col] == center_symbol &&
                            center_symbol == new_mat[0][col + 2]) {
                                diag2 = true;
                            }

                            if (diag1 && diag2) {
                                nr_comb++;
                                int diag_score = 21;
                                if (center_symbol == 7) {
                                    diag_score *= 2;
                                }
                                temp_score += diag_score;
                            } else {
                                if (diag1) {
                                    nr_comb++;
                                    int diag_score = 7;
                                    if (center_symbol == 7) {
                                        diag_score *= 2;
                                    }
                                    temp_score += diag_score;
                                }
                                if (diag2) {
                                    nr_comb++;
                                    int diag_score = 7;
                                    if (center_symbol == 7) {
                                        diag_score *= 2;
                                    }
                                    temp_score += diag_score;
                                }
                            }
                        }
                    }

                    for (int row = 0; row < max_rows; row++) {
                        for (int col = 0; col < m; col++) {
                            int sym = new_mat[row][col];
                            if (sym >= 0 && sym <= max_sym + 1 &&
                            dist[sym] == 0) {
                                dist[sym] = 1;
                                nr_sym++;
                            }
                        }
                    }

                    if (nr_sym <= 2) {
                        temp_score += 100;
                    } else if (nr_sym <= 4) {
                        temp_score += 15;
                    }

                    if (temp_score > max_score) {
                        max_score = temp_score;
                    }

                    free(dist);
                }
            }
        }

        printf("%d\n", max_score);

        for (int i = 0; i < n; i++) {
            free(new_mat[i]);
            free(mat[i]);
        }
        free(new_mat);
        free(mat);
    }
    return 0;
}
