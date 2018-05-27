/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：terminal.h
*   创 建 者：yunzhongke
*   创建日期：2018年05月27日
*   描    述：终端
*
================================================================*/


#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>



class Termianl : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Termianl(QWidget *parent = nullptr);

        ~Termianl();

    public slots:
        
        void clear_text();

    private:
        void m_init();

        void set_property();

        void set_layout();

        void set_connect();

        void set_style();

        void set_tabwidget();

    private:
        QTabWidget *tab;
        QWidget *ter_tab;
        QWidget *port_tab;
        QLabel *output_label; ///< 输出标签
        QLabel *input_label; ///< 输入标签
        QTextEdit *text_show; ///< 文本显示框
        QLineEdit *line_input; ///< 单行输入框
        QPushButton *store_button; ///< 保存按钮
        QPushButton *exit_button; ///< 退出按钮

        QHBoxLayout *h_layout1; ///< 第一行布局
        QHBoxLayout *h_layout2; ///< 第二行布局
        QVBoxLayout *v_layout; ///< 垂直布局
};

#endif //TERMINAL_H
