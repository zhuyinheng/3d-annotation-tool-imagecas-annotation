#pragma once
#include <memory>
#include "timeline.h"
#include "views/mesh_view.h"
#include "views/view.h"
#include "scene_model.h"
#include "view_context_3d.h"
#include "model/point_cloud_dataset.h"
#include "controllers/controller.h"
#include "controllers/preview_controller.h"
#include "views/point_cloud_view.h"
#include "views/annotation_view.h"
#include "views/add_keypoint_view.h"
#include "views/move_tool_view.h"
#include "views/add_bbox_view.h"
#include "views/status_bar_view.h"
#include "views/add_rectangle_view.h"
#include "views/controls/lookat.h"
#include "camera/camera_controls.h"
#include <filesystem>

namespace fs = std::filesystem;

class StudioViewController : public controllers::Controller {
private:
  int viewId;
  SceneModel sceneModel;
  SceneCamera sceneCamera;
  fs::path datasetPath;
  fs::path pointCloudPath;
  model::PointCloudDataset dataset;

  DatasetMetadata datasetMetadata;
  Timeline timeline;

  ViewContext3D viewContext;
  views::AnnotationView annotationView;
  views::MeshDrawable sceneMeshView;
  views::PointCloudView pointCloudView;
  views::controls::LookatControl lookatControl;

  // Tool views.
  views::AddKeypointView addKeypointView;
  views::MoveToolView moveToolView;
  views::AddBBoxView addBBoxView;
  views::AddRectangleView addRectangleView;

  views::StatusBarView statusBarView;

  // Sub-controllers
  std::shared_ptr<controllers::PreviewController> preview;

  camera::CameraControls cameraControls;

public:
  StudioViewController(fs::path datasetPath);
  void viewWillAppear(const views::Rect& r) override;

  void render() const;
  void refresh();

  bool leftButtonDown(double x, double y, InputModifier mod);
  bool leftButtonUp(double x, double y, InputModifier mod);
  bool mouseMoved(double x, double y, InputModifier mod);
  bool scroll(double xoffset, double yoffset, InputModifier mod);
  bool keypress(char character, const InputModifier mod) override;
  void resize(const views::Rect& r) override;

  void save() const;
  void load();
  void undo();

private:
  views::View3D& getActiveToolView();
  views::Rect previewRect() const;
  views::Rect statusBarRect() const;
  void updateViewContext(double x, double y, InputModifier mod);
  void loadPointCloud();
};
