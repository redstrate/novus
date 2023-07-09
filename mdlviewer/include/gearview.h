#pragma once

#include "filecache.h"
#include "mdlpart.h"
#include <QComboBox>
#include <QWidget>
#include <fmt/format.h>
#include <physis.hpp>

struct ModelInfo {
    int primaryID;
    int gearVersion = 1;
};

struct GearInfo {
    std::string name;
    Slot slot;
    ModelInfo modelInfo;

    std::string getMtrlPath(int raceID) {
        return fmt::format(
            "chara/equipment/e{gearId:04d}/material/v{gearVersion:04d}/mt_c{raceId:04d}e{gearId:04d}_{slot}_a.mtrl",
            fmt::arg("gearId", modelInfo.primaryID),
            fmt::arg("gearVersion", modelInfo.gearVersion),
            fmt::arg("raceId", raceID),
            fmt::arg("slot", physis_get_slot_name(slot)));
    }
};

struct GameData;

class GearView : public QWidget {
    Q_OBJECT
public:
    explicit GearView(GameData* data, FileCache& cache);

    /// Returns an inclusive list of races supported by the current gearset.
    std::vector<std::pair<Race, Subrace>> supportedRaces() const;

    /// Returns an inclusive list of genders supported by the current gearset.
    std::vector<Gender> supportedGenders() const;

    /// Returns an inclusive list of LoDs supported by the current gearset.
    int lodCount() const;

    void exportModel(const QString& fileName);

    MDLPart& part() const;

    Race currentRace = Race::Hyur;
    Subrace currentSubrace = Subrace::Midlander;
    Gender currentGender = Gender::Male;

Q_SIGNALS:
    void gearChanged();
    void modelReloaded();

    void raceChanged();
    void subraceChanged();
    void genderChanged();
    void levelOfDetailChanged();

    void faceChanged();
    void hairChanged();
    void earChanged();
    void tailChanged();

public Q_SLOTS:
    void clear();
    void addGear(GearInfo& gear);

    void setRace(Race race);
    void setSubrace(Subrace subrace);
    void setGender(Gender gender);
    void setLevelOfDetail(int lod);

    void setFace(int bodyVer);
    void setHair(int bodyVer);
    void setEar(int bodyVer);
    void setTail(int bodyVer);

    void reloadModel();
    void reloadRaceDeforms();

private:
    int currentLod = 0;

    uint32_t maxLod = 0;

    std::vector<GearInfo> gears;
    std::optional<int> face = 1, hair = 1, ear = 1, tail;

    MDLPart* mdlPart = nullptr;

    GameData* data;
    FileCache& cache;
};