/***************************************************************************
 *   Copyright (c) 2015 FreeCAD Developers                                 *
 *   Authors: Michael Hindley <hindlemp@eskom.co.za>                       *
 *            Ruan Olwagen <olwager@eskom.co.za>                           *
 *            Oswald van Ginkel <vginkeo@eskom.co.za>                      *
 *   Based on Force constraint by Jan Rheinländer                          *
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

#ifndef GUI_TASKVIEW_TaskFemConstraintPlaneRotation_H
#define GUI_TASKVIEW_TaskFemConstraintPlaneRotation_H

#include <QObject>

#include "TaskFemConstraint.h"
#include "ViewProviderFemConstraintPlaneRotation.h"


class Ui_TaskFemConstraintPlaneRotation;

namespace FemGui {
class TaskFemConstraintPlaneRotation : public TaskFemConstraint
{
    Q_OBJECT

public:
    TaskFemConstraintPlaneRotation(ViewProviderFemConstraintPlaneRotation *ConstraintView,QWidget *parent = nullptr);
    ~TaskFemConstraintPlaneRotation() override;
    const std::string getReferences() const override;

private Q_SLOTS:
    void onReferenceDeleted();
    void addToSelection();
    void removeFromSelection();

protected:
    bool event(QEvent *e) override;
    void changeEvent(QEvent *e) override;

private:
    void updateUI();
    Ui_TaskFemConstraintPlaneRotation* ui;

};

class TaskDlgFemConstraintPlaneRotation : public TaskDlgFemConstraint
{
    Q_OBJECT

public:
    TaskDlgFemConstraintPlaneRotation(ViewProviderFemConstraintPlaneRotation *ConstraintView);
    void open() override;
    bool accept() override;
    bool reject() override;
};

} //namespace FemGui

#endif // GUI_TASKVIEW_TaskFemConstraintPlaneRotation_H
