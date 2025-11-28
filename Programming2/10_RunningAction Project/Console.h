#pragma once

void gotoxy(int x, int y);
void hide_cursor();
void clear_area(int x1, int y1, int x2, int y2);

// --- [추가] 이중 버퍼링 함수 ---
void buffer_init();
void buffer_clear();
void buffer_write(int x, int y, const char* str);
void buffer_draw_char(int x, int y, char c);
void buffer_render();
// --- [추가] 이중 버퍼링 함수 ---