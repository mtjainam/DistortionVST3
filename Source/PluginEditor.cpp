/*
  ==============================================================================

 Jainam Mehta
 July-4-2024
 Distortion Plugin
 
 Hope you enjoy!


  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Distortion1AudioProcessorEditor::Distortion1AudioProcessorEditor (Distortion1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (800, 300);
  
    //attaching my slider knobs to their respective apvts thingies
    postAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, POST_ID, mPostSlider);
    
    driveAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, DRIVE_ID, mDriveSlider);
    
    threshAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, THRESH_ID, mThreshSlider);
    
    typeAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, TYPE_ID, mTypeSlider);
    
    //gui stuff
    
    mTypeSlider.setRange(1.0f, 3.0f, 1.0f);
    mTypeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    mTypeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(mTypeSlider);
    mTypeSlider.addListener(this);
    TypeLabel.setText("TYPE", juce::dontSendNotification);
    addAndMakeVisible(TypeLabel);
    
    mDriveSlider.setRange(0.3f, 10.0f, 0.01f);
    mDriveSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    mDriveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(mDriveSlider);
    mDriveSlider.addListener(this);
    DriveLabel.setText("DRIVE", juce::dontSendNotification);
    addAndMakeVisible(DriveLabel);
    
    mThreshSlider.setRange(1.0f, 50.0f, 1.0f);
    mThreshSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    mThreshSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(mThreshSlider);
    mThreshSlider.addListener(this);
    ThreshLabel.setText("THRESH", juce::dontSendNotification);
    addAndMakeVisible(ThreshLabel);

    mPostSlider.setRange(-27.0f, 27.0f, 0.01f);
    mPostSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    mPostSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(mPostSlider);
    mPostSlider.addListener(this);
    PostLabel.setText("POST", juce::dontSendNotification);
    addAndMakeVisible(PostLabel);
    
}

Distortion1AudioProcessorEditor::~Distortion1AudioProcessorEditor()
{
    
}

//==============================================================================
void Distortion1AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void Distortion1AudioProcessorEditor::resized()
{
    //more gui positioning stuff
    
    mTypeSlider.setBounds(50, 100, 100, 100);
    TypeLabel.setBounds(80, 60, 100, 50);

    mThreshSlider.setBounds(250, 100, 100, 100);
    ThreshLabel.setBounds(270, 60, 100, 50);
    
    mDriveSlider.setBounds(450, 100, 100, 100);
    DriveLabel.setBounds(475, 60, 100, 50);
    
    mPostSlider.setBounds(650, 100, 100, 100);
    PostLabel.setBounds(680, 60, 100, 50);
    
    
}

void Distortion1AudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    
    if(slider==&mTypeSlider){
        
        audioProcessor.mType = mTypeSlider.getValue();
    }
    
    if(slider==&mThreshSlider){
        
        audioProcessor.mThresh = mThreshSlider.getValue();
    }
    
    if(slider==&mDriveSlider){
        audioProcessor.mDrive = mDriveSlider.getValue();
    }
    
    if(slider==&mPostSlider){
        audioProcessor.mPost = mPostSlider.getValue();
    }
    
}
