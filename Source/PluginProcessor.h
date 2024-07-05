/*
  ==============================================================================

 Jainam Mehta
 July-4-2024
 Distortion Plugin
 
 Hope you enjoy!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <math.h>
#define TYPE_ID "type"
#define TYPE_NAME "Type"
#define THRESH_ID "thresh"
#define THRESH_NAME "Thresh"
#define DRIVE_ID "drive"
#define DRIVE_NAME "Drive"
#define POST_ID "post"
#define POST_NAME "Post"

//==============================================================================
/**
*/
class Distortion1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Distortion1AudioProcessor();
    ~Distortion1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float mType { 1.0 } ;
    
    float mThresh { 1.0 };
    
    float mDrive { 1.0 };
    
    float mPost { 0.0 };
    
  

private:
    


    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    

public:
    
    juce::AudioProcessorValueTreeState parameters;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion1AudioProcessor)
    
    
};
