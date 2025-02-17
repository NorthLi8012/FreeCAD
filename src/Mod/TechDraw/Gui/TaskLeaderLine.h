/***************************************************************************
 *   Copyright (c) 2019 WandererFan <wandererfan@gmail.com>                *
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

#ifndef TECHDRAWGUI_TASKTEXTLEADER_H
#define TECHDRAWGUI_TASKTEXTLEADER_H

#include <Mod/TechDraw/TechDrawGlobal.h>

#include <Base/Vector3D.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>

#include "QGTracker.h"

//TODO: make this a proper enum
#define TRACKERPICK 0
#define TRACKEREDIT 1
#define TRACKERCANCEL 2
#define TRACKERCANCELEDIT 3
#define TRACKERFINISHED 4
#define TRACKERSAVE 5

namespace TechDraw
{
class DrawPage;
class DrawView;
class DrawLeaderLine;
}

namespace TechDrawGui
{
class QGIView;
class QGIPrimPath;
class QGTracker;
class QGEPath;
class QGMText;
class QGILeaderLine;
class ViewProviderPage;
class ViewProviderLeader;
class Ui_TaskLeaderLine;

class TaskLeaderLine : public QWidget
{
    Q_OBJECT

public:
    TaskLeaderLine(TechDraw::DrawView* baseFeat,
                   TechDraw::DrawPage* page);
    TaskLeaderLine(TechDrawGui::ViewProviderLeader* leadVP);
    ~TaskLeaderLine() override;

public Q_SLOTS:
    void onTrackerClicked(bool b);
    void onCancelEditClicked(bool b);
    void onTrackerFinished(std::vector<QPointF> pts, TechDrawGui::QGIView* qgParent);

public:
    virtual bool accept();
    virtual bool reject();
    virtual void setCreateMode(bool b) { m_createMode = b; }
    virtual bool getCreateMode() { return m_createMode; }
    void updateTask();
    void saveButtons(QPushButton* btnOK,
                     QPushButton* btnCancel);
    void enableTaskButtons(bool b);
    void recomputeFeature();


protected Q_SLOTS:
    void onPointEditComplete();

protected:
    void trackerPointsFromQPoints(std::vector<QPointF> pts);
    void changeEvent(QEvent *e) override;
    void startTracker();
    void removeTracker();
    void abandonEditSession();

    void createLeaderFeature(std::vector<Base::Vector3d> converted);
    void updateLeaderFeature();
    void commonFeatureUpdate();
    void removeFeature();

    void blockButtons(bool b);
    void setUiPrimary();
    void setUiEdit();
    void enableTextUi(bool b);
    void enableVPUi(bool b);
    void setEditCursor(QCursor c);

    QGIView* findParentQGIV();
    int getPrefArrowStyle();
    double prefWeight() const;
    App::Color prefLineColor();

   void saveState();
   void restoreState();

private Q_SLOTS:
    void onStartSymbolChanged();
    void onEndSymbolChanged();
    void onColorChanged();
    void onLineWidthChanged();
    void onLineStyleChanged();

private:
    std::unique_ptr<Ui_TaskLeaderLine> ui;
    bool blockUpdate;

    QGTracker* m_tracker;
    
    ViewProviderPage* m_vpp;
    ViewProviderLeader* m_lineVP;
    TechDraw::DrawView* m_baseFeat;
    TechDraw::DrawPage* m_basePage;
    TechDraw::DrawLeaderLine* m_lineFeat;
    std::string m_leaderName;
    std::string m_leaderType;
    QGIView* m_qgParent;
    std::string m_qgParentName;

    std::vector<Base::Vector3d> m_trackerPoints;
    Base::Vector3d m_attachPoint;
    
    bool m_createMode;
    QGEPath* m_leadLine;

    QGTracker::TrackerMode m_trackerMode;
    Qt::ContextMenuPolicy  m_saveContextPolicy;
    bool m_inProgressLock;

    QGILeaderLine* m_qgLine;
    QPushButton* m_btnOK;
    QPushButton* m_btnCancel;
    
    int m_pbTrackerState;
    
    std::vector<Base::Vector3d> m_savePoints;
    double m_saveX;
    double m_saveY;

    bool m_haveMdi;
};

class TaskDlgLeaderLine : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskDlgLeaderLine(TechDraw::DrawView* baseFeat,
                      TechDraw::DrawPage* page);
    TaskDlgLeaderLine(TechDrawGui::ViewProviderLeader* leadVP);
    ~TaskDlgLeaderLine() override;

public:
    /// is called the TaskView when the dialog is opened
    void open() override;
    /// is called by the framework if an button is clicked which has no accept or reject role
    void clicked(int) override;
    /// is called by the framework if the dialog is accepted (Ok)
    bool accept() override;
    /// is called by the framework if the dialog is rejected (Cancel)
    bool reject() override;
    /// is called by the framework if the user presses the help button
    void helpRequested() override { return;}
    bool isAllowedAlterDocument() const override
                        { return false; }
    void update();

    void modifyStandardButtons(QDialogButtonBox* box) override;

protected:

private:
    TaskLeaderLine * widget;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace TechDrawGui

#endif // #ifndef TECHDRAWGUI_TASKTEXTLEADER_H
