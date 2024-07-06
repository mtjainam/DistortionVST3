cmake_minimum_required(VERSION 3.15)

# Project name and version
project(DistortionVST3 VERSION 1.0.0)

# Add the JUCE framework
add_subdirectory(JUCE)

# Add your source files
add_executable(DistortionVST3
    Source/Main.cpp
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

# Link with JUCE modules
target_link_libraries(DistortionVST3
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_audio_basics
        juce::juce_core
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
)