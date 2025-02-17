/***************************************************************************
 *   Copyright (c) 2013 Luke Parry <l.parry@warwick.ac.uk>                 *
 *   Copyright (c) 2019 Franck Jullien <franck.jullien@gmail.com>          *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef TECHDRAWGUI_QGIVBALLOON_H
#define TECHDRAWGUI_QGIVBALLOON_H

#include <Mod/TechDraw/TechDrawGlobal.h>

#include <QColor>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QObject>
#include <QStyleOptionGraphicsItem>

#include <Base/Vector3D.h>

#include "QGCustomText.h"
#include "QGIView.h"


namespace TechDraw {
class DrawViewBalloon;
class DrawView;
}

namespace TechDraw {
class BaseGeom;
class AOC;
}

namespace TechDrawGui
{
class QGIArrow;
class QGIDimLines;
class QGIViewBalloon;

class QGIBalloonLabel : public QGraphicsObject
{
Q_OBJECT

public:
    QGIBalloonLabel();
    ~QGIBalloonLabel() override = default;

    enum {Type = QGraphicsItem::UserType + 141};
    int type() const override { return Type;}

    QRectF boundingRect() const override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint( QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget = nullptr ) override;
    void setLabelCenter();
    void setPosFromCenter(const double &xCenter, const double &yCenter);
    double X() const { return posX; }
    double Y() const { return posY; }              //minus posY?
    
    void setFont(QFont f);
    QFont getFont() { return m_labelText->font(); }
    void setDimString(QString t);
    void setDimString(QString t, qreal maxWidth);
    void setPrettySel();
    void setPrettyPre();
    void setPrettyNormal();
    void setColor(QColor c);

    bool verticalSep;
    std::vector<int> seps;

    QGCustomText* getDimText() { return m_labelText; }
    void setDimText(QGCustomText* newText) { m_labelText = newText; }

    bool hasHover;

    QGIViewBalloon *parent;

Q_SIGNALS:
    void dragging(bool);
    void hover(bool state);
    void selected(bool state);
    void dragFinished();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    QGCustomText* m_labelText;
    QColor m_colNormal;

    double posX;
    double posY;
    bool m_ctrl;
    bool m_drag;
    
private:
};

//*******************************************************************

class TechDrawGuiExport QGIViewBalloon : public QGIView
{
    Q_OBJECT

public:
    enum {Type = QGraphicsItem::UserType + 140};

    explicit QGIViewBalloon();
    ~QGIViewBalloon() override = default;

    void setViewPartFeature(TechDraw::DrawViewBalloon *obj);
    int type() const override { return Type;}

    void drawBorder() override;
    void updateView(bool update = false) override;
    void paint( QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget = nullptr ) override;

    QString getLabelText();
    void placeBalloon(QPointF pos);
    TechDraw::DrawViewBalloon *dvBalloon;
    void setPrettyPre();
    void setPrettySel();
    void setPrettyNormal();

    void setGroupSelection(bool b) override;
    virtual QGIBalloonLabel* getBalloonLabel() { return balloonLabel; }

    QColor getNormalColor() override;
    int prefDefaultArrow() const;
    bool prefOrthoPyramid() const;


public Q_SLOTS:
    void balloonLabelDragged(bool ctrl);
    void balloonLabelDragFinished();
    void select(bool state);
    void hover(bool state);
    void updateBalloon(bool obtuse = false);

protected:
    void draw() override;
    void drawBalloon(bool dragged = false);
    QVariant itemChange( GraphicsItemChange change,
                                 const QVariant &value ) override;
    virtual void setSvgPens();
    virtual void setPens();
    QString getPrecision();

protected:
    bool hasHover;
    QGIBalloonLabel* balloonLabel;
    QGIDimLines* balloonLines;
    QGIDimLines* balloonShape;
    QGIArrow* arrow;
    double m_lineWidth;
    bool m_obtuse;
    void parentViewMousePressed(QGIView *view, QPointF pos);
    QGIView *parent;           //used to create edit dialog

    TechDraw::DrawView* getSourceView() const;
    bool m_dragInProgress;
    bool m_originDragged = false;
    bool m_ctrl;
    Base::Vector3d m_saveOffset;


};

} // namespace

#endif // TECHDRAWGUI_QGIVBALLOON_H
