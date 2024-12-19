#pragma once
#include <QWidget>
#include <QApplication>
#include <QPainter>
#include "ActivitateService.h"
#include "Observer.h"
#include <QImage>
class HistogramaGUI:public QWidget,public Observer{
private:
    ActivitateService& srv;
public:
    HistogramaGUI(ActivitateService& srv):srv{srv}{
        srv.addObserver(this);
    }
    void update()override{
        repaint();
    }
    void paintEvent(QPaintEvent* ev) override{
        QPainter p{this};
        int x=10;
        for(auto& l:srv.getAllListaActivitai()) {
            p.drawRect(x, 40, rand()%10,rand()%100+50);
            x+=40;
        }
    }
};