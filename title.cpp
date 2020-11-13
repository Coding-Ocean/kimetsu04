#include"libOne.h"
void title() {
    struct TEXT {
        const char* str = 0;
        int size = 0;
        float x = 0;
        float y = 0;
    };
    //文字列
    font("UD デジタル 教科書体 NP-B");
    struct TEXT texts[3] = {
    "鬼滅の命令書",300,0,1080/3,
    "　ねずこ編",300,0,1080/3*2,
    "",360,0,1080
    };
    for (int i = 0; i < 3; i++)
        texts[i].x = 200;
    
    //輪郭 contour
    float cx = 0;//ずらすベクトルｘ
    float cy = 0;//ずらすベクトルｙ
    float cw = 10;//ずらす量
    int n = 16;
    angleMode(DEGREES);
    float deg = 360.0f / n;

    for (int j = 0; j < 3; j++) {
        textSize(texts[j].size);
        for (int i = 0; i < n + 1; i++) {
            if (i < n) {
                //輪郭
                fill(20, 20, 20);
                cx = cos(deg * i) * cw;
                cy = sin(deg * i) * cw;
                text(texts[j].str, texts[j].x + cx, texts[j].y + cy);
            }
            else {
                //本体
                fill(255, 255, 255);
                text(texts[j].str, texts[j].x, texts[j].y);
            }
        }
    }
}