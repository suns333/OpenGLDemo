//
//  main.cpp
//  OpenGLDemo
//
//  Created by 周洋 on 2020/7/5.
//  Copyright © 2020 周洋. All rights reserved.
//

#include <stdio.h>

#include <GLShaderManager.h>
#include "GLTools.h"
#include <GLUT/GLUT.h>

//着色器管理类
GLShaderManager shaderManager;
//批次类
GLBatch triangleBatch;
GLfloat blockSize = 0.1f;
//正方形的顶点坐标
GLfloat vVerts[] = {
    -blockSize, blockSize, 0.0f,
    blockSize, blockSize, 0.0f,
    blockSize, -blockSize, 0.0f,
    -blockSize, -blockSize, 0.0f,
};

GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;
GLfloat zRot = 0.0f;

//窗口大小改变时的回调
void changeSize(int w, int h) {
    //设置视口
    glViewport(0, 0, w, h);
}

void renderSence() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {0.0f, 1.0f, 0.0f, 0.0f};
    
    //初始化矩阵
    M3DMatrix44f mFinalTransform, mTranslationMatrix, mRotationMatrix;
    //平移矩阵
    m3dTranslationMatrix44(mTranslationMatrix, xPos, yPos, 0);
    
    zRot+=5.0f;
    //渲染矩阵
    m3dRotationMatrix44(mRotationMatrix, m3dDegToRad(zRot), 0.0f, 0.0f, 1.0f);
    //矩阵的合成
    m3dMatrixMultiply44(mFinalTransform, mTranslationMatrix, mRotationMatrix);
    //将矩阵的结果提交到固定着色器中进行绘制
    shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vRed);
    triangleBatch.Draw();
    
    glutSwapBuffers();
}

void setupRC() {
    //设置背景颜色
    glClearColor(0.2f, 0.54f, 0.33f, 1);
    //没有着色器，在OpenGL 核心框架中是无法进行任何渲染的。初始化一个渲染管理器，暂时使用固定着色器
    shaderManager.InitializeStockShaders();
    
    triangleBatch.Begin(GL_POINT_BIT, 4);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

void specialKeys(int key, int x, int y) {
    GLfloat stepSize = 0.025f;
    if(key == GLUT_KEY_UP) {
        yPos += stepSize;
    }
    if(key == GLUT_KEY_DOWN) {
        yPos -= stepSize;
    }
    if(key == GLUT_KEY_LEFT) {
        xPos -= stepSize;
    }
    if(key == GLUT_KEY_RIGHT) {
        xPos += stepSize;
    }
    
    if(yPos < -1 + blockSize) {
        yPos = -1 + blockSize;
    }
    if(yPos > 1 - blockSize) {
        yPos = 1 - blockSize;
    }
    if(xPos < -1 + blockSize) {
        xPos = -1 + blockSize;
    }
    if(xPos > 1 - blockSize) {
        xPos = 1 - blockSize;
    }
    
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("haha");
    
    //GLUT内部运行一个消息循环，在合适的时机，会调用我们注册的函数
    //注册重塑函数回调
    glutReshapeFunc(changeSize);
    //注册显示函数回调
    glutDisplayFunc(renderSence);
    //注册特殊函数
    glutSpecialFunc(specialKeys);
    /*
    初始化一个GLEW库,确保OpenGL API对程序完全可用。
    在试图做任何渲染之前，要检查确定驱动程序的初始化过程中没有任何问题
    */
    GLenum status = glewInit();
    if(status != GLEW_OK) {
        printf("GLEW Error:%s\n",glewGetErrorString(status));
        return 1;
    }
    
    //设置渲染环境
    setupRC();
    
    glutMainLoop();
    
    return 0;
}
