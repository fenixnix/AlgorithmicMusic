#include "qmusicinstrument.h"

QMusicInstrument::QMusicInstrument()
{
    music.SetMode();
    contour.TrapezoidaEnvelope(0.08f,0.01f,0.1f,1.0f);
}

void QMusicInstrument::Play(int index)
{
    chipTune.generateData("Pulse",music.TunePitch(index),contour);
    PlayChip();
}

void QMusicInstrument::PlayChip()
{
    player.Play(chipTune.buffer);
}

void QMusicInstrument::Bass()
{
    contour.Clear();
    contour.Push(0.012,1.0);
    contour.Push(0.032,0.5);
    contour.Push(0.032,0.4);
    contour.Push(0.042,0.0);
    chipTune.generateData("Sine",25,contour);
    PlayChip();
}

void QMusicInstrument::SideDrum()
{
    contour.TrapezoidaEnvelope(0.00f,0.02f,0.02f,1.0f);
    chipTune.generateData("Noise",880,contour);
    PlayChip();
}

void QMusicInstrument::Tomtom()
{
    contour.Clear();
    contour.Push(0.012,1.0);
    contour.Push(0.017,1.0);
    contour.Push(0.017,0.5);
    contour.Push(0.02,0.3);
    contour.Push(0.04,0.2);
    contour.Push(0.005,0.0);
    chipTune.generateData("Sine",230,contour);
    PlayChip();
}

void QMusicInstrument::HighHat()
{
    contour.TrapezoidaEnvelope(0.08f,0.03f,0.05f,0.2f);
    chipTune.generateData("Noise",8000,contour);
    PlayChip();
}

void QMusicInstrument::SetMode(QString mode)
{
    music.SetMode(mode.toStdString());
}

int QMusicInstrument::GetModeNoteCount()
{
    return music.TuneCount();
}
