#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;


struct Node { char data[1000]; Node* next; };
struct Stack { Node* top; };
struct QNode { char action[50]; char content[500]; QNode* next; };
struct Queue { QNode* front; QNode* rear; };

const char* folderPath = "C:\\Users\\Haise_\\source\\repos\\Project1\\LuuTruText\\";

void setColor(int c) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); }
void goToXY(int x, int y) { COORD c = { (SHORT)x, (SHORT)y }; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); }


int getDisplayWidth(const char* s) {
    int width = 0;
    while (*s) {
        if ((*s & 0xc0) != 0x80) width++;
        s++;
    }
    return width;
}


void init(Stack* s) { 
    s->top = NULL; 
}
bool empty(Stack s) { 
    return s.top == NULL; 
}
void push(Stack* s, const char* str) {
    Node* n = new Node; strcpy(n->data, str);
    n->next = s->top; s->top = n;
}
char* pop(Stack* s) {
    if (empty(*s)) return NULL;
    Node* t = s->top; static char res[1000];
    strcpy(res, t->data); s->top = t->next; delete t;
    return res;
}
void initQ(Queue* q) { q->front = q->rear = NULL; }
void pushQ(Queue* q, const char* a, const char* c) {
    QNode* n = new QNode; strcpy(n->action, a); strncpy(n->content, c, 499);
    n->content[499] = '\0'; n->next = NULL;
    if (!q->rear) q->front = q->rear = n;
    else { q->rear->next = n; q->rear = n; }
}


void showFullScreen(const char* text) {
    system("cls");
    setColor(11);
    printf("┌─────────────────────────────────────────────────────────────────────────┐\n");
    setColor(15);
    if (strlen(text) == 0) {
        printf("│ "); 
        const char* msg = "(Văn bản hiện đang trống...)";
        printf("%s", msg);
        for (int i = 0; i < 71 - getDisplayWidth(msg); i++) printf(" ");
        printf(" │\n");
    }
    else {
        char* temp = _strdup(text);
        char* line = strtok(temp, "\n");
        while (line != NULL) {
            printf("│ "); 
            printf("%s", line);
            int len = getDisplayWidth(line);
            for (int i = 0; i < 71 - len; i++) printf(" ");
            printf(" │\n");
            line = strtok(NULL, "\n");
        }
        free(temp);
    }
    setColor(11);
    printf("└─────────────────────────────────────────────────────────────────────────┘\n");
    setColor(14); printf(" >> Bấm phím bất kỳ để thoát chế độ xem...");
    _getch();
}


void showHistory(Queue* q) {
    system("cls");
    setColor(11);
    printf("┌─────────────────┬───────────────────────────────────────────────────────┐\n");
    printf("│ HÀNH ĐỘNG       │ NỘI DUNG CHI TIẾT                                     │\n");
    printf("├─────────────────┼───────────────────────────────────────────────────────┤\n");

    QNode* t = q->front;
    if (!t) {
        printf("│ "); setColor(8);
        const char* msg = "(Chưa có lịch sử thao tác)";
        printf("%s", msg);
        for (int i = 0; i < 71 - getDisplayWidth(msg); i++) printf(" ");
        setColor(11); printf(" │\n");
    }
    else {
        while (t) {
            setColor(11); printf("│ ");
            setColor(10); printf("%s", t->action);
            int aLen = getDisplayWidth(t->action);
            for (int i = 0; i < 15 - aLen; i++) printf(" ");

            setColor(11); printf(" │ ");
            setColor(15);
            char preview[55]; strncpy(preview, t->content, 54); preview[54] = '\0';
            printf("%s", preview);
            int cLen = getDisplayWidth(preview);
            for (int i = 0; i < 53 - cLen; i++) printf(" ");

            setColor(11); printf(" │\n");
            t = t->next;
        }
    }
    printf("└─────────────────┴───────────────────────────────────────────────────────┘\n");
    setColor(14); printf(" >> Bấm phím bất kỳ để quay lại...");
    _getch();
}


vector<string> getTxtFiles() {
    vector<string> files; char searchPath[250]; sprintf(searchPath, "%s*.txt", folderPath);
    WIN32_FIND_DATAA findData; HANDLE hFind = FindFirstFileA(searchPath, &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do { if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) files.push_back(findData.cFileName); } 
        while (FindNextFileA(hFind, &findData));
        FindClose(hFind);
    }
    return files;
}

string showFileList() {
    vector<string> files = getTxtFiles(); if (files.empty()) return "";
    int sel = 0, maxDisplay = 8;
    while (true) {
        system("cls"); setColor(11);
        goToXY(12, 8); printf("┌────────────── CHỌN TỆP TIN ĐỂ MỞ ──────────────┐");
        for (int i = 0; i < maxDisplay; i++) { goToXY(12, 9 + i); printf("│                                                │"); }
        goToXY(12, 9 + maxDisplay); printf("└────────────────────────────────────────────────┘");
        for (int i = 0; i < (int)files.size() && i < maxDisplay; i++) {
            goToXY(15, 9 + i);
            if (i == sel) { setColor(14); printf(" ► %-40s", files[i].c_str()); }
            else { setColor(7); printf("   %-40s", files[i].c_str()); }
        }
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) sel = (sel - 1 + (int)files.size()) % (int)files.size();
            if (key == 80) sel = (sel + 1) % (int)files.size();
        }
        else if (key == 13) return files[sel];
        else if (key == 27) return "";
    }
}

void inputWindow(const char* title, char* output, int maxLen) {
    setColor(11);
    goToXY(12, 10); printf("┌────────────────────────────────────────────────┐");
    goToXY(12, 11); printf("│ "); printf("%s", title);
    int tLen = getDisplayWidth(title);
    for (int i = 0; i < 46 - tLen; i++) printf(" "); printf(" │");
    goToXY(12, 12); printf("├────────────────────────────────────────────────┤");
    goToXY(12, 13); printf("│ >                                              │");
    goToXY(12, 14); printf("└────────────────────────────────────────────────┘");
    goToXY(16, 13); setColor(15);
    fgets(output, maxLen, stdin); output[strcspn(output, "\n")] = 0;
}

// --- Giao diện Main UI ---
void drawUI(const char* text, int tab, int sel, const char* status) {
    const char* tabs[] = { "TỆP TIN", "CHỈNH SỬA", "HIỂN THỊ", "TRỢ GIÚP" };
    const char* menu[4][5] = {
        {"Mở tệp (Danh sách)", "Lưu tệp (.txt)", "Tạo mới trang", "Thoát chương trình"},
        {"Thêm nội dung", "Ghi đè tất cả", "Hoàn tác (Undo)", "Làm lại (Redo)", "Xóa sạch văn bản"},
        {"Xem toàn màn hình", "Lịch sử thao tác", "Thống kê số ký tự"},
        {"Hướng dẫn phím tắt"}
    };
    int size[4] = { 4, 5, 3, 1 };

    system("cls"); setColor(11);
    printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         MINI TEXT EDITOR                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════╝\n");
    printf("\n ");
    for (int i = 0; i < 4; i++) {
        if (i == tab) { setColor(14); printf(" [%s] ", tabs[i]); }
        else { setColor(8); printf("  %s  ", tabs[i]); }
    }
    printf("\n");
    setColor(9); printf("\n┌───────────────────────────── LỰA CHỌN ───────────────────────────────┐\n");
    for (int i = 0; i < size[tab]; i++) {
        printf("│ ");
        if (i == sel) {
            setColor(14); printf(" ► "); printf("%s", menu[tab][i]);
            int len = getDisplayWidth(menu[tab][i]);
            for (int j = 0; j < 65 - len; j++) printf(" ");
        } else {
            setColor(7); printf("   "); printf("%s", menu[tab][i]);
            int len = getDisplayWidth(menu[tab][i]);
            for (int j = 0; j < 65 - len; j++) printf(" ");
        }
        setColor(9); printf(" │\n");
    }
    printf("└──────────────────────────────────────────────────────────────────────┘\n");
    printf("\n┌─────────────────────────── NỘI DUNG NHANH ───────────────────────────┐\n");
    setColor(15);
    if (strlen(text) == 0) {
        printf("│ "); printf("(Văn bản đang trống...)");
        for (int i = 0; i < 68 - getDisplayWidth("(Văn bản đang trống...)"); i++) printf(" ");
        printf(" │\n");
    } else {
        char temp[61]; strncpy(temp, text, 60); temp[60] = '\0';
        printf("│ "); printf("%s", temp);
        int len = getDisplayWidth(temp);
        for (int j = 0; j < 68 - len; j++) printf(" "); printf(" │\n");
    }
    setColor(9); printf("└──────────────────────────────────────────────────────────────────────┘\n");
    setColor(8); printf("\n TRẠNG THÁI: "); setColor(10); printf("%s", status);
    printf("\n\n"); setColor(8); printf(" ──────────────────────────────────────────────────────────────────────\n ");
    setColor(7); printf("[←][→]:"); setColor(15); printf(" Tab  ");
    setColor(7); printf("[↑][↓]:"); setColor(15); printf(" Chọn  ");
    setColor(7); printf("[ENTER]:"); setColor(15); printf(" OK  ");
    setColor(7); printf("[ESC]:"); setColor(15); printf(" Thoát");
}

int main() {
    SetConsoleOutputCP(65001); SetConsoleCP(65001);
    Stack undo, redo; init(&undo); init(&redo);
    Queue history; initQ(&history);
    char text[1000] = ""; char input[1000], fileName[120];
    int tab = 0, sel = 0; char status[100] = "SẴN SÀNG";

    while (1) {
        drawUI(text, tab, sel, status);
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 75) { tab = (tab - 1 + 4) % 4; sel = 0; }
            if (key == 77) { tab = (tab + 1) % 4; sel = 0; }
            if (key == 72) sel--; if (key == 80) sel++;
            int maxSel = (tab == 0) ? 4 : (tab == 1) ? 5 : (tab == 2) ? 3 : 1;
            if (sel < 0) sel = maxSel - 1; if (sel >= maxSel) sel = 0;
        }
        else if (key == 27) break;
        else if (key == 13) {
            if (tab == 0) {
                if (sel == 0) {
                    string selected = showFileList();
                    if (selected != "") {
                        char fullPath[250]; sprintf(fullPath, "%s%s", folderPath, selected.c_str());
                        FILE* f = fopen(fullPath, "r");
                        if (f) {
                            push(&undo, text); text[0] = 0; char line[500];
                            while (fgets(line, 500, f)) strcat(text, line);
                            fclose(f); strcpy(status, "ĐÃ MỞ FILE THÀNH CÔNG");
                            pushQ(&history, "MỞ TỆP", selected.c_str());
                        }
                    } else strcpy(status, "ĐÃ HỦY MỞ FILE");
                }
                else if (sel == 1) {
                    char mkdirCmd[250]; sprintf(mkdirCmd, "if not exist \"%s\" mkdir \"%s\"", folderPath, folderPath);
                    system(mkdirCmd); inputWindow("Tên tệp (không cần .txt):", fileName, 100);
                    char fullPath[250]; sprintf(fullPath, "%s%s.txt", folderPath, fileName);
                    FILE* f = fopen(fullPath, "w");
                    if (f) { fprintf(f, "%s", text); fclose(f); strcpy(status, "ĐÃ LƯU TỆP"); pushQ(&history, "LƯU TỆP", fileName); }
                }
                else if (sel == 2) { push(&undo, text); text[0] = '\0'; strcpy(status, "ĐÃ TẠO TRANG MỚI"); pushQ(&history, "TẠO MỚI", "Trang giấy trắng"); }
                else if (sel == 3) break;
            }
            else if (tab == 1) {
                if (sel == 0) {
                    inputWindow("Nhập nội dung thêm:", input, 1000);
                    push(&undo, text); strcat(text, input); pushQ(&history, "THÊM", input);
                }
                else if (sel == 1) {
                    inputWindow("Nhập nội dung đè:", input, 1000);
                    push(&undo, text); strcpy(text, input); pushQ(&history, "GHI ĐÈ", input);
                }
                else if (sel == 2 && !empty(undo)) {
                    push(&redo, text); strcpy(text, pop(&undo)); strcpy(status, "HOÀN TÁC (UNDO)");
                    pushQ(&history, "HOÀN TÁC", "Quay lại bước trước");
                }
                else if (sel == 3 && !empty(redo)) {
                    push(&undo, text); strcpy(text, pop(&redo)); strcpy(status, "LÀM LẠI (REDO)");
                    pushQ(&history, "LÀM LẠI", "Khôi phục bước đã Undo");
                }
                else if (sel == 4) { push(&undo, text); text[0] = '\0'; strcpy(status, "ĐÃ XÓA SẠCH"); pushQ(&history, "XÓA SẠCH", "Xóa toàn bộ"); }
            }
            else if (tab == 2) {
                if (sel == 0) showFullScreen(text);
                else if (sel == 1) showHistory(&history);
                else if (sel == 2) sprintf(status, "TỔNG SỐ KÝ TỰ: %d", getDisplayWidth(text));
            }
            else if (tab == 3) {
                system("cls"); setColor(11);
                printf("\n ┌────────────────────┬────────────────────────────────────┐\n");
                printf(" │    PHÍM TẮT        │        CHỨC NĂNG CHÍNH             │\n");
                printf(" ├────────────────────┼────────────────────────────────────┤\n");
                printf(" │  "); setColor(14); printf("[↑] / [↓]       "); setColor(11); printf("  │  "); setColor(15); printf("Di chuyển chọn chức năng          "); setColor(11); printf("│\n");
                printf(" │  "); setColor(14); printf("[←] / [→]       "); setColor(11); printf("  │  "); setColor(15); printf("Thay đổi danh mục (Tabs)          "); setColor(11); printf("│\n");
                printf(" │  "); setColor(14); printf("[ENTER]         "); setColor(11); printf("  │  "); setColor(15); printf("Xác nhận thực hiện lệnh           "); setColor(11); printf("│\n");
                printf(" │  "); setColor(14); printf("[ESC]           "); setColor(11); printf("  │  "); setColor(15); printf("Thoát chương trình                "); setColor(11); printf("│\n");
                printf(" └────────────────────┴────────────────────────────────────┘\n");
                setColor(14); printf("\n >> Bấm phím bất kỳ để quay lại...");
                _getch();
            }
        }
    }
    return 0;
}
