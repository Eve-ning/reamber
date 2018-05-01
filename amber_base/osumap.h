#ifndef COM_MAP_H
#define COM_MAP_H


#include "hitobjectlist.h"
#include "timingpointlist.h"
#include "breakpointlist.h"
#include <QDebug>

class  osuMap
{
public:

    enum class cSampleSet
    {
        NORMAL,
        SOFT  ,
        DRUM  ,
        AUTO
    };
    enum class cGameMode
    {
        STANDARD,
        TAIKO,
        CTB,
        MANIA
    };

    // CONSTRUCTORS
    osuMap();

    // LOADERS
    void loadMap(QString newMapString);
    void loadMap(QFileInfo newMapPath);
    void loadMap(QStringList newMapStringList);

    // Runs a list of parameters on qDebug
    void getInfo() const;

    // SETTERS
    void setOsuFileName      (QString        newOsuFileName    ){ osuFileName     = newOsuFileName    ; }
    void setAudioFileName    (QString        newAudioFileName  ){ audioFileName   = newAudioFileName  ; }
    void setAudioLeadIn      (int            newAudioLeadIn    ){ audioLeadIn     = newAudioLeadIn    ; }
    void setPreviewTime      (int            newPreviewTime    ){ previewTime     = newPreviewTime    ; }
    void setCountdown        (bool           newCountdown      ){ countdown       = newCountdown      ; }
    void setSampleSet        (cSampleSet     newSampleSet      ){ sampleSet       = newSampleSet      ; }
    void setStackLeniency    (double         newStackLeniency  ){ stackLeniency   = newStackLeniency  ; }
    void setGameMode         (cGameMode      newGameMode       ){ gameMode        = newGameMode       ; }
    void setLetterbox        (bool           newLetterbox      ){ letterbox       = newLetterbox      ; }
    void setSpecialStyle     (bool           newSpecialStyle   ){ specialStyle    = newSpecialStyle   ; }
    void setWidescreen       (bool           newWidescreen     ){ widescreen      = newWidescreen     ; }
    void setDistanceSpacing  (double         newDistanceSpacing){ distanceSpacing = newDistanceSpacing; }
    void setBeatDivisor      (int            newBeatDivisor    ){ beatDivisor     = newBeatDivisor    ; }
    void setGridSize         (int            newGridSize       ){ gridSize        = newGridSize       ; }
    void setTimelineZoom     (double         newTimelineZoom   ){ timelineZoom    = newTimelineZoom   ; }
    void setTitle            (QString        newTitle          ){ title           = newTitle          ; }
    void setUnicodeTitle     (QString        newUnicodeTitle   ){ unicodeTitle    = newUnicodeTitle   ; }
    void setArtist           (QString        newArtist         ){ artist          = newArtist         ; }
    void setUnicodeArtist    (QString        newUnicodeArtist  ){ unicodeArtist   = newUnicodeArtist  ; }
    void setCreator          (QString        newCreator        ){ creator         = newCreator        ; }
    void setDifficultyName   (QString        newDifficultyName ){ difficultyName  = newDifficultyName ; }
    void setSource           (QString        newSource         ){ source          = newSource         ; }
    void setTags             (QStringList    newTags           ){ tags            = newTags           ; }
    void setBeatmapID        (int            newBeatmapID      ){ beatmapID       = newBeatmapID      ; }
    void setBeatmapSetID     (int            newBeatmapSetID   ){ beatmapSetID    = newBeatmapSetID   ; }
    void setHP               (double         newHP             ){ HP              = newHP             ; }
    void setCS               (double         newCS             ){ CS              = newCS             ; }
    void setOD               (double         newOD             ){ OD              = newOD             ; }
    void setAR               (double         newAR             ){ AR              = newAR             ; }
    void setSliderMult       (double         newSliderMult     ){ sliderMult      = newSliderMult     ; }
    void setSliderTick       (double         newSliderTick     ){ sliderTick      = newSliderTick     ; }
    void setBGFileName       (QString        newBGFileName     ){ bgFileName      = newBGFileName     ; }
    void setVideoFileName    (QString        newVideoFileName  ){ videoFileName   = newVideoFileName  ; }
    void setBreakPList       (BreakPointList newBreakPList     ){ breakPList      = newBreakPList     ; }
    void setOM_HOList        (HitObjectList     newHOList      ){ OM_HOList       = newHOList      ; }
    void setOM_TPList        (TimingPointList     newTimingPointList      ){ curTimingPointList       = newTimingPointList      ; }

    // GETTERS
    QString        getOsuFileName      () const { return osuFileName     ; }
    QString        getAudioFileName    () const { return audioFileName   ; }
    int            getAudioLeadIn      () const { return audioLeadIn     ; }
    int            getPreviewTime      () const { return previewTime     ; }
    bool           getCountdown        () const { return countdown       ; }
    cSampleSet     getSampleSet        () const { return sampleSet       ; }
    double         getStackLeniency    () const { return stackLeniency   ; }
    cGameMode      getGameMode         () const { return gameMode        ; }
    bool           getLetterbox        () const { return letterbox       ; }
    bool           getSpecialStyle     () const { return specialStyle    ; }
    bool           getWidescreen       () const { return widescreen      ; }
    double         getDistanceSpacing  () const { return distanceSpacing ; }
    int            getBeatDivisor      () const { return beatDivisor     ; }
    int            getGridSize         () const { return gridSize        ; }
    double         getTimelineZoom     () const { return timelineZoom    ; }
    QString        getTitle            () const { return title           ; }
    QString        getUnicodeTitle     () const { return unicodeTitle    ; }
    QString        getArtist           () const { return artist          ; }
    QString        getUnicodeArtist    () const { return unicodeArtist   ; }
    QString        getCreator          () const { return creator         ; }
    QString        getDifficultyName   () const { return difficultyName  ; }
    QString        getSource           () const { return source          ; }
    QStringList    getTags             () const { return tags            ; }
    int            getBeatmapID        () const { return beatmapID       ; }
    int            getBeatmapSetID     () const { return beatmapSetID    ; }
    double         getHP               () const { return HP              ; }
    double         getCS               () const { return CS              ; }
    double         getOD               () const { return OD              ; }
    double         getAR               () const { return AR              ; }
    double         getSliderMult       () const { return sliderMult      ; }
    double         getSliderTick       () const { return sliderTick      ; }
    QString        getBGFileName       () const { return bgFileName      ; }
    QString        getVideoFileName    () const { return videoFileName   ; }
    BreakPointList getBreakPList       () const { return breakPList      ; }
    HitObjectList     getOM_HOList        () const { return OM_HOList       ; }
    TimingPointList     getOM_TPList        () const { return curTimingPointList       ; }

    // OPERS

    // MISC
    void copyAudioFileTo (QFileInfo copyLocation);
    void copyOsuFileTo   (QFileInfo copyLocation);
    void copyBGFileTo    (QFileInfo copyLocation);
    void copyAllTo       (QFileInfo copyLocation);

protected:

    // General
    QString    audioFileName;
    int        audioLeadIn;
    int        previewTime;
    bool       countdown;
    cSampleSet sampleSet;
    double     stackLeniency;
    cGameMode  gameMode;
    bool       letterbox;
    bool       specialStyle;
    bool       widescreen;

    // Editor
    double  distanceSpacing;
    int     beatDivisor;
    int     gridSize;
    double  timelineZoom;

    // Metadata
    QString title;
    QString unicodeTitle;
    QString artist;
    QString unicodeArtist;
    QString creator;
    QString difficultyName;
    QString source;
    QStringList tags;
    int     beatmapID;
    int     beatmapSetID;

    // Difficulty
    double  HP;
    double  CS;
    double  OD;
    double  AR;
    double  sliderMult;
    double  sliderTick;

    // Misc
    QString bgFileName;
    QString videoFileName;
    QString osuFileName;

    // Breaks
    BreakPointList breakPList;

    // HitObject and TimingPoint
    HitObjectList OM_HOList;
    TimingPointList curTimingPointList;

private:

    QList<int> findMapSettings(QStringList &mapSList);

//    enum FIND {
//        E_AUDIOFILENAME  ,
//        E_AUDIOLEADIN    ,
//        E_PREVIEWTIME    ,
//        E_COUNTDOWN      ,
//        E_SAMPLESET      ,
//        E_STACKLENIENCY  ,
//        E_GAMEMODE       ,
//        E_LETTERBOX      ,
//        E_SPECIALSTYLE   ,
//        E_WIDESCREEN     ,
//        E_DISTANCESPACING,
//        E_BEATDIVISOR    ,
//        E_GRIDSIZE       ,
//        E_TIMELINEZOOM   ,
//        E_TITLE          ,
//        E_UNICODETITLE   ,
//        E_ARTIST         ,
//        E_UNICODEARTIST  ,
//        E_CREATOR        ,
//        E_DIFFICULTYNAME ,
//        E_SOURCE         ,
//        E_TAGS           ,
//        E_BEATMAPID      ,
//        E_BEATMAPSETID   ,
//        E_HP             ,
//        E_CS             ,
//        E_OD             ,
//        E_AR             ,
//        E_SLIDERMULT     ,
//        E_SLIDERTICK     ,
//        E_BGFILENAME     ,
//        E_VIDEOFILENAME  ,
//        E_BREAKP         ,
//        E_OM_HOLIST      ,
//        E_OM_TPLIST
//    };
};

#endif // COM_MAP_H
