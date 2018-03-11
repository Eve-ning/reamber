#ifndef COM_TP_H
#define COM_TP_H
#include "amber.h"

class cOM_TP
{
public:
    cOM_TP();
    cOM_TP(QString TP);

    double          getOffset        () const { return offset        ; }
    double          getCode          () const { return code          ; }
    unsigned short  getMetronome     () const { return metronome     ; }
    unsigned short  getSampleSet     () const { return sampleSet     ; }
    unsigned short  getSampleSetIndex() const { return sampleSetIndex; }
    unsigned short  getVolume        () const { return volume        ; }
    bool            getIsBPM         () const { return isBPM         ; }
    bool            getIsKiai        () const { return isKiai        ; }

    void setOffset        (double          newOffset        );
    void setCode          (double          newCode          );
    void setMetronome     (unsigned short  newMetronome     );
    void setSampleSet     (unsigned short  newSampleSet     );
    void setSampleSetIndex(unsigned short  newSameplSetIndex);
    void setVolume        (unsigned short  newVolume        );
    void setType          (bool            newType          );
    void setKiai          (bool            newKiai          );

    double getValue() const;
    void   setValue(double newValue) ;

    QString toString();

protected:
    double          offset        ;
    double          code          ;
    unsigned short  metronome     ;
    unsigned short  sampleSet     ;
    unsigned short  sampleSetIndex;
    unsigned short  volume        ;
    bool            isBPM         ;
    bool            isKiai        ;

};

#endif // COM_TP_H
