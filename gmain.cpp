#include"libOne.h"
#include"title.h"
class NEZU {
    VECTOR3 P[6];
    float Len = 100;
    float HalfLen = Len / 2;
    int State = 0;
    float Angle = 0;
    float RotSpeed = 1.0f;
    float Vec = 0;
    float MoveSpeed = HalfLen / 360;
    int Cols = 0;
    int Rows = 0;
public:
    void createTile() {
        angleMode(DEGREES);
        //右、上、左、下の点
        for (int i = 0; i < 4; i++) {
            P[i].x = cos(90.0f * i) * HalfLen;
            P[i].y = -sin(90.0f * i) * HalfLen;
        }
        //中央右の点
        P[4].x = 0.333f * HalfLen;
        P[4].y = 0;
        //中央左の点
        P[5].x = -0.333f * HalfLen;
        P[5].y = 0;
        //列数、行数
        Cols = int(width / HalfLen);
        Rows = int(height / HalfLen) + 2;
    }
    void moveTile() {
        if (State != 0) {
            Vec += MoveSpeed;
            Angle += RotSpeed;
        }

        if (State == 0) {
            Vec = 0;
            Angle = 0;
            P[4].x = 0.333f * HalfLen;
            P[4].y = 0;
            P[5].x = -0.333f * HalfLen;
            P[5].y = 0;
            if (isTrigger(KEY_SPACE)) {
                State = 1;
            }
        }
        else if (State == 1) {
            if (isTrigger(KEY_SPACE)) {
                State = 2;
            }
        }
        else if (State == 2) {
            P[0].x = cos(Angle) * HalfLen;
            P[2].x = -cos(Angle) * HalfLen;
            if (isTrigger(KEY_SPACE)) {
                P[0].x = HalfLen;
                P[2].x = -HalfLen;
                State = 3;
            }
        }
        else if (State == 3) {
            P[1].y = cos(Angle) * HalfLen;
            P[3].y = -cos(Angle) * HalfLen;
            if (isTrigger(KEY_SPACE)) {
                P[1].y = -HalfLen;
                P[3].y = HalfLen;
                State = 4;
            }
        }
        else if (State == 4) {
            P[4].x = cos(Angle) * HalfLen;
            P[5].x = -cos(Angle) * HalfLen;
            if (isTrigger(KEY_SPACE)) {
                State = 0;
            }
        }
    }
private:
    /*
    void DrawTile(float x, float y) {
        //正方形の輪郭
        line(P[0].x + x, P[0].y + y, P[1].x + x, P[1].y + y);
        line(P[1].x + x, P[1].y + y, P[2].x + x, P[2].y + y);
        line(P[2].x + x, P[2].y + y, P[3].x + x, P[3].y + y);
        line(P[3].x + x, P[3].y + y, P[0].x + x, P[0].y + y);
        //P[4]に向かう線
        line(P[0].x + x, P[0].y + y, P[4].x + x, P[4].y + y);
        line(P[1].x + x, P[1].y + y, P[4].x + x, P[4].y + y);
        line(P[3].x + x, P[3].y + y, P[4].x + x, P[4].y + y);
        //P[5]に向かう線
        line(P[1].x + x, P[1].y + y, P[5].x + x, P[5].y + y);
        line(P[2].x + x, P[2].y + y, P[5].x + x, P[5].y + y);
        line(P[3].x + x, P[3].y + y, P[5].x + x, P[5].y + y);
        //中央の縦線
        line(P[1].x + x, P[1].y + y, P[3].x + x, P[3].y + y);
    }
    */
    void DrawTile(float x, float y) {
        int i, j;
        //正方形の輪郭
        for (i = 0; i < 4; i++) {
            j = (i + 1) % 4;//1 -> 2 -> 3 -> 0 と変化
            line(P[i].x + x, P[i].y + y, P[j].x + x, P[j].y + y);
        }
        for (int i = 0; i < 3; i++) {
            //P[4]に向かう線
            j = (i + 3) % 4;//3 -> 0 -> 1 と変化
            line(P[j].x + x, P[j].y + y, P[4].x + x, P[4].y + y);
            //P[5]に向かう線
            j = i + 1;//1 -> 2 -> 3 と変化
            line(P[j].x + x, P[j].y + y, P[5].x + x, P[5].y + y);
        }
        //中央の縦線
        line(P[1].x + x, P[1].y + y, P[3].x + x, P[3].y + y);
    }
    void DrawObi() {
        noStroke();
        //obi position
        float obiY = height / 3;
        float alpha = 190;
        //nezu shita obi
        fill(165, 186, 95, alpha);
        rect(0, obiY - 10, width, 10);
        //nezu obi
        float obiW = 70;
        float obiH = 50;
        int col = int(width / obiW) + 1;
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < col; i++) {
                if ((j + i) % 2 == 0)
                    fill(220, 220, 220, alpha);
                else
                    fill(220, 0, 0, alpha);
                rect(i * obiW, obiY + j * obiH, obiW, obiH);
            }
        }
        //nezu obi himo
        fill(252, 204, 119, alpha);
        rect(0, obiY + obiH * 1.5f - 8, width, 16);
    }
public:
    void draw() {
        strokeWeight(1);
        stroke(100);
        for (int j = 0; j < Rows; j++) {
            for (int i = 0; i < Cols; i++) {
                float ofsX = (j % 2) * HalfLen;
                float x = ofsX + i * Len - HalfLen;
                float y = j * HalfLen - HalfLen;
                if ((j / 2 + i) % 2) {
                    x += Vec;
                    y += Vec;
                    if (Vec > HalfLen) {
                        Vec = 0;
                    }
                }
                DrawTile(x, y);
            }
        }
        DrawObi();
    }
};

void background() {
    clear(90, 54, 90);
    fill(250, 167, 183);
    rect(0, 0, width, height);
}

void gmain() {
    ShowCursor(FALSE);
    window(1920,1080, full);
    class NEZU nezu;
    nezu.createTile();
    while (notQuit) {
        nezu.moveTile();
        background();
        nezu.draw();
        title();
    }
    ShowCursor(TRUE);
}