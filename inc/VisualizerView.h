/*
 * LocheGSplicer
 * Copyright (C) 2012 Jeff P. Houde (Lochemage)
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */


#ifndef VISUALIZER_VIEW_H
#define VISUALIZER_VIEW_H

#include <Constants.h>
#include <QGLWidget>
#include <QTimer>


class GCodeObject;
struct ExtruderData;
class QProgressDialog;

class VisualizerView : public QGLWidget
{
   Q_OBJECT

public:
   VisualizerView(const PreferenceData& prefs);
   virtual ~VisualizerView();

   /**
    * Adds an object into the visualizer.
    *
    * @param[in]  object     The object.
    */
   bool addObject(GCodeObject* object);
   void removeObject(GCodeObject* object);

   void clearObjects();

   void setShaderEnabled(bool enabled);

   QSize minimumSizeHint() const;
   QSize sizeHint() const;

   void setLayerDrawHeight(double height);

   bool regenerateGeometry();

   const QString& getError() const;

public slots:
   void onBackgroundColorChanged(const QColor& color);

   void setXTranslation(double pos);
   void setYTranslation(double pos);
   void setZTranslation(double pos);

   void setXRotation(double angle);
   void setYRotation(double angle);
   void setZRotation(double angle);

   void setZoom(double zoom);

   void updateTick();

signals:
   void xTranslationChanged(double pos);
   void yTranslationChanged(double pos);
   void zTranslationChanged(double pos);

   void xRotationChanged(double angle);
   void yRotationChanged(double angle);
   void zRotationChanged(double angle);

   void zoomChanged(double zoom);

protected:
   void initializeGL();
   bool updateCamera();
   void paintGL();
   void resizeGL(int width, int height);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void wheelEvent(QWheelEvent* event);

   bool genObject(VisualizerObjectData& object, QProgressDialog& progressDialog);
   void callObject(const VisualizerObjectData& object);
   void drawObject(const VisualizerObjectData& object);
   void drawPlatform();

private:

   /**
    * Generate geometry data for the given object.
    */
   bool generateGeometry(VisualizerObjectData& data, QProgressDialog& progressDialog);
   void addGeometryPoint(double* buffer, int& index, const QVector3D& point);

   void freeBuffers(VisualizerObjectData& data);

   double mCameraRot[AXIS_NUM_NO_E];
   double mCameraTrans[AXIS_NUM_NO_E];
   double mCameraZoom;

   double mCameraRotTarget[AXIS_NUM_NO_E];
   double mCameraTransTarget[AXIS_NUM_NO_E];
   double mCameraZoomTarget;
   QPoint mLastPos;

   QTimer* mUpdateTimer;

   const PreferenceData& mPrefs;

   GLint  mShaderProgram;
   double mCameraRotDirection;

   double mLayerDrawHeight;
   
   std::vector<VisualizerObjectData> mObjectList;

   QString mError;
};

#endif // VISUALIZER_VIEW_H
