#ifndef COM_MAP_H
#define COM_MAP_H


#include "amber_base/hitobjectlist.h"
#include "amber_base/timingpointlist.h"
#include "amber_base/breakpointlist.h"

#include <QFileInfo>

#include "amber_base/baseclass_inc.h"
#include <QDebug>

class  osuMap
{
public:

    // CONSTRUCTORS
    osuMap();

    // LOADERS
    void loadMap(QString newMapString);
    void loadMap(QFileInfo newMapPath);
    void loadMap(QStringList newMapStringList);

    // Runs a list of parameters on qDebug
    void getInfo() const;

    // SETTERS
    void setOsuFileName      (CommonFile      osuFileName_    ){ osuFileName        = osuFileName_    ; }
    void setAudioFileName    (CommonFile      audioFileName_  ){ audioFileName      = audioFileName_  ; }
    void setAudioLeadIn      (int             audioLeadIn_    ){ audioLeadIn        = audioLeadIn_    ; }
    void setPreviewTime      (int             previewTime_    ){ previewTime        = previewTime_    ; }
    void setCountdown        (bool            countdown_      ){ countdown          = countdown_      ; }
    void setSampleSet        (SampleSet       sampleSet_      ){ sampleSet          = sampleSet_      ; }
    void setStackLeniency    (double          stackLeniency_  ){ stackLeniency      = stackLeniency_  ; }
    void setGameMode         (GameMode        gameMode_       ){ gameMode           = gameMode_       ; }
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
    void setBGFileName       (CommonFile      bgFileName_     ){ bgFileName         = bgFileName_     ; }
    void setVideoFileName    (CommonFile      videoFileName_  ){ videoFileName      = videoFileName_  ; }
    void setBreakPList       (BreakPointList  breakPList_     ){ breakPList         = breakPList_     ; }
    void setHitObjectList    (HitObjectList   hitObjectList_  ){ hitObjectList      = hitObjectList_  ; }
    void setTimingPointList  (TimingPointList timingPointList_){ timingPointList    = timingPointList_; }

    // GETTERS
    CommonFile      getOsuFileName      () const { return osuFileName    ; }
    CommonFile      getAudioFileName    () const { return audioFileName  ; }
    int             getAudioLeadIn      () const { return audioLeadIn    ; }
    int             getPreviewTime      () const { return previewTime    ; }
    bool            getCountdown        () const { return countdown      ; }
    SampleSet       getSampleSet        () const { return sampleSet      ; }
    double          getStackLeniency    () const { return stackLeniency  ; }
    GameMode        getGameMode         () const { return gameMode       ; }
    bool            getLetterbox        () const { return letterbox      ; }
    bool            getSpecialStyle     () const { return specialStyle   ; }
    bool            getWidescreen       () const { return widescreen     ; }
    double          getDistanceSpacing  () const { return distanceSpacing; }
    int             getBeatDivisor      () const { return beatDivisor    ; }
    int             getGridSize         () const { return gridSize       ; }
    double          getTimelineZoom     () const { return timelineZoom   ; }
    QString         getTitle            () const { return title          ; }
    QString         getUnicodeTitle     () const { return unicodeTitle   ; }
    QString         getArtist           () const { return artist         ; }
    QString         getUnicodeArtist    () const { return unicodeArtist  ; }
    QString         getCreator          () const { return creator        ; }
    QString         getDifficultyName   () const { return difficultyName ; }
    QString         getSource           () const { return source         ; }
    QStringList     getTags             () const { return tags           ; }
    int             getBeatmapID        () const { return beatmapID      ; }
    int             getBeatmapSetID     () const { return beatmapSetID   ; }
    double          getHP               () const { return HP             ; }
    double          getCS               () const { return CS             ; }
    double          getOD               () const { return OD             ; }
    double          getAR               () const { return AR             ; }
    double          getSliderMult       () const { return sliderMult     ; }
    double          getSliderTick       () const { return sliderTick     ; }
    CommonFile      getBGFileName       () const { return bgFileName     ; }
    CommonFile      getVideoFileName    () const { return videoFileName  ; }
    BreakPointList  getBreakPList       () const { return breakPList     ; }
    HitObjectList   getHitObjectList    () const { return hitObjectList  ; }
    TimingPointList getTimingPointList  () const { return timingPointList; }

    // OPERS

    // MISC
    void copyAudioFileTo (QFileInfo copyLocation);
    void copyOsuFileTo   (QFileInfo copyLocation);
    void copyBGFileTo    (QFileInfo copyLocation);
    void copyAllTo       (QFileInfo copyLocation);

protected:

    // General
    CommonFile audioFileName;
    Offset     audioLeadIn;
    Offset     previewTime;
    bool       countdown;
    SampleSet  sampleSet;
    double     stackLeniency;
    GameMode   gameMode;
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
    CommonFile bgFileName;
    CommonFile videoFileName;
    CommonFile osuFileName;

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
