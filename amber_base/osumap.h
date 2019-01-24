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
    void setOsuFileName      (QString         osuFileName_    ){ osuFileName        = osuFileName_    ; }
    void setAudioFileName    (QString         audioFileName_  ){ audioFileName      = audioFileName_  ; }
    void setAudioLeadIn      (int             audioLeadIn_    ){ audioLeadIn        = audioLeadIn_    ; }
    void setPreviewTime      (int             previewTime_    ){ previewTime        = previewTime_    ; }
    void setCountdown        (bool            countdown_      ){ countdown          = countdown_      ; }
    void setSampleSet        (cSampleSet      sampleSet_      ){ sampleSet          = sampleSet_      ; }
    void setStackLeniency    (double          stackLeniency_  ){ stackLeniency      = stackLeniency_  ; }
    void setGameMode         (cGameMode       gameMode_       ){ gameMode           = gameMode_       ; }
    void setLetterbox        (bool            letterbox_      ){ letterbox          = letterbox_      ; }
    void setSpecialStyle     (bool            specialStyle_   ){ specialStyle       = specialStyle_   ; }
    void setWidescreen       (bool            widescreen_     ){ widescreen         = widescreen_     ; }
    void setDistanceSpacing  (double          distanceSpacing_){ distanceSpacing    = distanceSpacing_; }
    void setBeatDivisor      (int             beatDivisor_    ){ beatDivisor        = beatDivisor_    ; }
    void setGridSize         (int             gridSize_       ){ gridSize           = gridSize_       ; }
    void setTimelineZoom     (double          timelineZoom_   ){ timelineZoom       = timelineZoom_   ; }
    void setTitle            (QString         title_          ){ title              = title_          ; }
    void setUnicodeTitle     (QString         unicodeTitle_   ){ unicodeTitle       = unicodeTitle_   ; }
    void setArtist           (QString         artist_         ){ artist             = artist_         ; }
    void setUnicodeArtist    (QString         unicodeArtist_  ){ unicodeArtist      = unicodeArtist_  ; }
    void setCreator          (QString         creator_        ){ creator            = creator_        ; }
    void setDifficultyName   (QString         difficultyName_ ){ difficultyName     = difficultyName_ ; }
    void setSource           (QString         source_         ){ source             = source_         ; }
    void setTags             (QStringList     tags_           ){ tags               = tags_           ; }
    void setBeatmapID        (int             beatmapID_      ){ beatmapID          = beatmapID_      ; }
    void setBeatmapSetID     (int             beatmapSetID_   ){ beatmapSetID       = beatmapSetID_   ; }
    void setHP               (double          HP_             ){ HP                 = HP_             ; }
    void setCS               (double          CS_             ){ CS                 = CS_             ; }
    void setOD               (double          OD_             ){ OD                 = OD_             ; }
    void setAR               (double          AR_             ){ AR                 = AR_             ; }
    void setSliderMult       (double          sliderMult_     ){ sliderMult         = sliderMult_     ; }
    void setSliderTick       (double          sliderTick_     ){ sliderTick         = sliderTick_     ; }
    void setBGFileName       (QString         bgFileName_     ){ bgFileName         = bgFileName_     ; }
    void setVideoFileName    (QString         videoFileName_  ){ videoFileName      = videoFileName_  ; }
    void setBreakPList       (BreakPointList  breakPList_     ){ breakPList         = breakPList_     ; }
    void setHitObjectList    (HitObjectList   hitObjectList_  ){ hitObjectList      = hitObjectList_  ; }
    void setTimingPointList  (TimingPointList timingPointList_){ timingPointList    = timingPointList_; }

    // GETTERS
    QString         getOsuFileName      () const { return osuFileName       ; }
    QString         getAudioFileName    () const { return audioFileName     ; }
    int             getAudioLeadIn      () const { return audioLeadIn       ; }
    int             getPreviewTime      () const { return previewTime       ; }
    bool            getCountdown        () const { return countdown         ; }
    cSampleSet      getSampleSet        () const { return sampleSet         ; }
    double          getStackLeniency    () const { return stackLeniency     ; }
    cGameMode       getGameMode         () const { return gameMode          ; }
    bool            getLetterbox        () const { return letterbox         ; }
    bool            getSpecialStyle     () const { return specialStyle      ; }
    bool            getWidescreen       () const { return widescreen        ; }
    double          getDistanceSpacing  () const { return distanceSpacing   ; }
    int             getBeatDivisor      () const { return beatDivisor       ; }
    int             getGridSize         () const { return gridSize          ; }
    double          getTimelineZoom     () const { return timelineZoom      ; }
    QString         getTitle            () const { return title             ; }
    QString         getUnicodeTitle     () const { return unicodeTitle      ; }
    QString         getArtist           () const { return artist            ; }
    QString         getUnicodeArtist    () const { return unicodeArtist     ; }
    QString         getCreator          () const { return creator           ; }
    QString         getDifficultyName   () const { return difficultyName    ; }
    QString         getSource           () const { return source            ; }
    QStringList     getTags             () const { return tags              ; }
    int             getBeatmapID        () const { return beatmapID         ; }
    int             getBeatmapSetID     () const { return beatmapSetID      ; }
    double          getHP               () const { return HP                ; }
    double          getCS               () const { return CS                ; }
    double          getOD               () const { return OD                ; }
    double          getAR               () const { return AR                ; }
    double          getSliderMult       () const { return sliderMult        ; }
    double          getSliderTick       () const { return sliderTick        ; }
    QString         getBGFileName       () const { return bgFileName        ; }
    QString         getVideoFileName    () const { return videoFileName     ; }
    BreakPointList  getBreakPList       () const { return breakPList        ; }
    HitObjectList   getHitObjectList    () const { return hitObjectList     ; }
    TimingPointList getTimingPointList  () const { return timingPointList; }

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
    HitObjectList hitObjectList;
    TimingPointList timingPointList;

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
