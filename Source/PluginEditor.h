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
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Distortion1AudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         public juce::Slider::Listener
                                          
                                        
                                       
{
public:
    Distortion1AudioProcessorEditor (Distortion1AudioProcessor&);
    ~Distortion1AudioProcessorEditor() override;
    
    void sliderValueChanged(juce::Slider *slider) override;
    
    

    //==============================================================================
    void paint (juce::Graphics&) override;
    
    void resized() override;

private:
 
    Distortion1AudioProcessor& audioProcessor;
    
    juce::Slider mTypeSlider;
    
    juce::Slider mThreshSlider;
    
    juce::Slider mDriveSlider;
    
    juce::Slider mPostSlider;
    
    juce::Label TypeLabel;
    
    juce::Label ThreshLabel;
    
    juce::Label DriveLabel;
    
    juce::Label PostLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion1AudioProcessorEditor)
    
public:
    
std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> typeAttach;
    
std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> threshAttach;
    
std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> driveAttach;
    
std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> postAttach;

    
    
};
