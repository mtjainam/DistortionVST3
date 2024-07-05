/*
  ==============================================================================

 Jainam Mehta
 July-4-2024
 Distortion Plugin
 
 Hope you enjoy!

//lfg
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
Distortion1AudioProcessor::Distortion1AudioProcessor()

#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
parameters(*this, nullptr, "PARAMETERS", createParameterLayout())

 

#endif
{
}

juce::AudioProcessorValueTreeState::ParameterLayout Distortion1AudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

        params.push_back(std::make_unique<juce::AudioParameterFloat>(POST_ID, POST_NAME, -27.0f, 27.0f, 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(DRIVE_ID, DRIVE_NAME, 0.3f, 10.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(THRESH_ID, THRESH_NAME, 1.0f, 50.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(TYPE_ID, TYPE_NAME, 1.0f, 3.0f, 1.0f));


        // Add more parameters as needed

        return { params.begin(), params.end() };
}
Distortion1AudioProcessor::~Distortion1AudioProcessor()
{
}

//==============================================================================
const juce::String Distortion1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Distortion1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Distortion1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Distortion1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Distortion1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Distortion1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Distortion1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Distortion1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Distortion1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Distortion1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Distortion1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Distortion1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Distortion1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Distortion1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    float mThresh2 = 51 - mThresh;
    const float ceiling = juce::Decibels::decibelsToGain(-0.1f);


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        

            
        {
            if (mType == 1)  //algo 1
            {
                channelData[sample] = mDrive * channelData[sample];
                
                    if (channelData[sample] < 0.005 * mThresh2 || channelData[sample] > 0.005 * -mThresh2)
                    {
                        channelData[sample] = channelData[sample];
                    }
                    
                    if (channelData[sample] >= 0.005 *mThresh2 )
                    {
                        channelData[sample] = 0.005 * mThresh2;
                    }
                    
                    if (channelData[sample] <= 0.005 * -mThresh2)
                    {
                        channelData[sample] = 0.005 * -mThresh2;
                    }
                    
            }
            
            
            
            if (mType == 2) //algo 2
            {
                channelData[sample] = mDrive * channelData[sample];
                channelData[sample] = tanhf ( mThresh * channelData[sample] );
            }
            
            if (mType == 3)  //algo 3
            {
                channelData[sample] = mDrive * channelData[sample];
                
                if (channelData[sample] >= 0.01 * mThresh2)
                {
                    channelData[sample] = (channelData[sample]-mThresh2) * 0.5 + mThresh2;
                }
                
                if (channelData[sample] < 0.01 * mThresh2 || channelData[sample] > 0.01 * mThresh2)
                {
                    channelData[sample] = channelData[sample];
                }
                
                if (channelData[sample] <= 0.01 * -mThresh2)
                {
                    channelData[sample] = (channelData[sample]+mThresh2) * 0.5 - mThresh2;
                }
                    
            }
            
        channelData[sample] = juce::Decibels::decibelsToGain(mPost) * channelData[sample];//post-gain applied to sample

//making sure I don't destroy your speakers <3
        
            if ( channelData[sample] > ceiling )
            {
                channelData[sample] = ceiling;
            }
            
            else if ( channelData[sample] < -ceiling )
            {
                channelData[sample] = -ceiling;
            }
            
            
            
        }

    }
}

//==============================================================================
bool Distortion1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Distortion1AudioProcessor::createEditor()
{
    return new Distortion1AudioProcessorEditor (*this);
}

//==============================================================================
void Distortion1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
    auto state = parameters.copyState();
        std::unique_ptr<juce::XmlElement> xml (state.createXml());
        copyXmlToBinary (*xml, destData);
}

void Distortion1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));

        if (xml != nullptr)
            if (xml->hasTagName (parameters.state.getType()))
                parameters.replaceState (juce::ValueTree::fromXml (*xml));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Distortion1AudioProcessor();
}
