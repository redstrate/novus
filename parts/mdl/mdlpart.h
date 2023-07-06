#pragma once

#include <QWidget>
#include <optional>
#include <physis.hpp>

#include "renderer.hpp"

struct GameData;

class VulkanWindow;
class StandaloneWindow;

class MDLPart : public QWidget {
    Q_OBJECT

public:
    explicit MDLPart(GameData* data);

    void exportModel(const QString& fileName);

    int lastX = -1;
    int lastY = -1;

    enum class CameraMode {
        None,
        Orbit,
        Move
    };

    CameraMode cameraMode = CameraMode::None;
    float pitch = 0.0f;
    float yaw = 0.0f;
    float cameraDistance = 5.0f;
    glm::vec3 position {0, 0, 0};

    std::unique_ptr<physis_Skeleton> skeleton;

Q_SIGNALS:
    void modelChanged();
    void skeletonChanged();

public Q_SLOTS:
    /// Clears all stored MDLs.
    void clear();

    /// Adds a new MDL with a list of materials used.
    void addModel(physis_MDL mdl, std::vector<physis_Material> materials, int lod);

    /// Sets the skeleton any skinned MDLs should bind to.
    void setSkeleton(physis_Skeleton skeleton);

    /// Clears the current skeleton.
    void clearSkeleton();

    void reloadBoneData();
    void reloadRenderer();

private:
    RenderMaterial createMaterial(const physis_Material& mat);

    void calculateBoneInversePose(physis_Skeleton& skeleton, physis_Bone& bone, physis_Bone* parent_bone);
    void calculateBone(physis_Skeleton& skeleton, physis_Bone& bone, const physis_Bone* parent_bone);

    GameData* data = nullptr;

    std::vector<RenderModel> models;

    struct BoneData {
        glm::mat4 localTransform, finalTransform, inversePose;
    };

    std::vector<BoneData> boneData;

    Renderer* renderer;
    VulkanWindow* vkWindow;
    StandaloneWindow* standaloneWindow;
    bool firstTimeSkeletonDataCalculated = false;
};