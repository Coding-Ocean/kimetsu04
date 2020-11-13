#include"libOne.h"
void title() {
    struct TEXT {
        const char* str = 0;
        int size = 0;
        float x = 0;
        float y = 0;
    };
    //������
    font("UD �f�W�^�� ���ȏ��� NP-B");
    struct TEXT texts[3] = {
    "�S�ł̖��ߏ�",300,0,1080/3,
    "�@�˂�����",300,0,1080/3*2,
    "",360,0,1080
    };
    for (int i = 0; i < 3; i++)
        texts[i].x = 200;
    
    //�֊s contour
    float cx = 0;//���炷�x�N�g����
    float cy = 0;//���炷�x�N�g����
    float cw = 10;//���炷��
    int n = 16;
    angleMode(DEGREES);
    float deg = 360.0f / n;

    for (int j = 0; j < 3; j++) {
        textSize(texts[j].size);
        for (int i = 0; i < n + 1; i++) {
            if (i < n) {
                //�֊s
                fill(20, 20, 20);
                cx = cos(deg * i) * cw;
                cy = sin(deg * i) * cw;
                text(texts[j].str, texts[j].x + cx, texts[j].y + cy);
            }
            else {
                //�{��
                fill(255, 255, 255);
                text(texts[j].str, texts[j].x, texts[j].y);
            }
        }
    }
}