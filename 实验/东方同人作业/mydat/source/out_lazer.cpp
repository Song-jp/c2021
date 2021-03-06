#include "../include/GV.h"
#include <math.h>
#include <stdio.h>

/* 平面向量 */
typedef struct {
    double x, y;
} Vector2_t;

/* diff ← 向量 p - q */
void Vector2Diff(Vector2_t *diff, const Vector2_t *p, const Vector2_t *q){
    diff->x = p->x - q->x;
    diff->y = p->y - q->y;
}

/* 向量 p 和 q 的内积 */
double Vector2InnerProduct(const Vector2_t *p, const Vector2_t *q){
    return p->x * q->x + p->y * q->y;
}

/* 向量 p 和 q 的外积 */
double Vector2OuterProduct(const Vector2_t *p, const Vector2_t *q){
    return p->x * q->y - p->y * q->x;
}

//求点和线段的距离
double get_distance(double x, double y, double x1, double y1, 
                    double x2, double y2){
    double dx,dy,a,b,t,tx,ty;
    double distance;
    dx = (x2 - x1); dy = (y2 - y1);
    a = dx*dx + dy*dy;
    b = dx * (x1 - x) + dy * (y1 - y);
    t = -b / a;
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    tx = x1 + dx * t;
    ty = y1 + dy * t;
    distance = sqrt((x - tx)*(x - tx) + (y - ty)*(y - ty));
    return distance;
}

//返回点与点的距离
double get_pt_and_pt(pt_t p1, pt_t p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

//点是否在圆中。0：没有 1：在
double question_point_and_circle(pt_t p, pt_t rp,double r){
    double dx=p.x-rp.x,dy=p.y-rp.y;
    if(dx*dx + dy*dy < r*r)    return 1;
    else                    return 0;
}

//交换
void swap_double(double *n, double *m){
    double t=*m;
    *m=*n;*n=t;
}

//通过3个点返回所成夹角
double get_sita(pt_t pt0,pt_t pt1,pt_t rpt){
    /* 计算向量 C→P 和 C→Q 所形成的角θ以及旋转方向*/
    Vector2_t c, p, q; /* 输入数据 */
    Vector2_t cp;      /* 向量 C→P */
    Vector2_t cq;      /* 向量 C→Q */
    double s;          /* 外积：(C→P) × (C→Q) */
    double t;          /* 内积：(C→P) ・ (C→Q) */
    double theta;      /* θ (弧度) */

    /*将 c，p，q 设定为所想的值。*/
    c.x = pt0.x;    c.y = pt0.y;
    p.x = pt1.x;    p.y = pt1.y;
    q.x = rpt.x;    q.y = rpt.y;

    /* 计算旋转方向以及角度θ。*/
    Vector2Diff(&cp, &p, &c);          /* cp ← p - c   */
    Vector2Diff(&cq, &q, &c);          /* cq ← q - c   */
    s = Vector2OuterProduct(&cp, &cq); /* s ← cp × cq */
    t = Vector2InnerProduct(&cp, &cq); /* t ← cp ・ cq */
    theta = atan2(s, t);
    return theta;
}

//判定长方形和圆是否相碰
int hitjudge_square_and_circle(pt_t pt[4], pt_t rpt, double r){
    int i;
    double a[4],b[4];//a:傾き　b:y切片
    double x=rpt.x,y=rpt.y;
	double theta,theta2;

	/*判断圆中是否有长方形4个顶点中的某一个*/
    for(i=0;i<4;i++){
        if(question_point_and_circle(pt[i],rpt,r)==1)
            return 1;
    }
	/*到此为止*/

	/*判定长方形中是否有物体进入*/

    theta =get_sita(pt[0],pt[1],rpt);//3点所成的角1
    theta2=get_sita(pt[2],pt[3],rpt);//3点所成的角2

    if(0<=theta && theta<=PI/2 && 0<=theta2 && theta2<=PI/2)
        return 1;

    /*到此为止*/

	/*求线段和点的距离*/
    for(i=0;i<4;i++){
        if(get_distance(rpt.x,rpt.y,pt[i].x,pt[i].y,pt[(i+1)%4].x,pt[(i+1)%4].y)<r)
            return 1;
    }
	/*到此为止*/

    return 0;//如果哪里都没有碰撞的话就没有碰撞判定
}


int out_lazer(){
    int i,j;
    pt_t sqrp[4],rpt={ch.x,ch.y};//长方形四个顶点和圆的中心
    //激光数次循环
    for(i=0;i<LAZER_MAX;i++){
        //如果激光已经登录且设定了碰撞判定
        if(lazer[i].flag>0 && lazer[i].hantei!=0){
            for(j=0;j<4;j++){//设定激光的四个顶点
                sqrp[j].x=lazer[i].outpt[j].x;
                sqrp[j].y=lazer[i].outpt[j].y;
            }
			//长方形和圆的接触判定
            if(hitjudge_square_and_circle(sqrp,rpt,CRANGE))
                return 1;
        }
    }
    return 0;
}