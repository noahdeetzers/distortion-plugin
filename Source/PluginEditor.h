/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DistLNF : public juce::LookAndFeel_V4
{
public:
    DistLNF()
    {
        setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::textBoxTextColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::backgroundColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::trackColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::thumbColourId, juce::Colour(241,85,73));
    }
};

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    juce::Slider::SliderLayout getSliderLayout(juce::Slider&) override
    {
        juce::Slider::SliderLayout layout;
        layout.textBoxBounds = juce::Rectangle<int>(25, 110, 50, 20);
        return layout;
    }
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        const auto gainSkin = juce::Drawable::createFromImageData(BinaryData::SliderClear_svg, BinaryData::SliderClear_svgSize);
        juce::AffineTransform rotator;
        if (!slider.isMouseOverOrDragging())
        {
           // gainSkin->draw(g, 1.f, juce::AffineTransform());
        }
        else
        {
           // gainSkin->draw(g, 1.f, juce::AffineTransform());
        }
        //gainSkin->draw(g, 1.0f, rotator.rotated((float)sliderPosProportional * rotaryEndAngle, gainSkin->getWidth() * 0.5f, gainSkin->getHeight() * 0.5f));
        gainSkin->draw(g, 1.0f, rotator.rotated((float)sliderPosProportional * rotaryEndAngle, (float)(gainSkin->getWidth() / 2), (float)(gainSkin->getHeight() / 2)));
    }
    OtherLookAndFeel()
    {
        setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::textBoxTextColourId, juce::Colours::lightgrey);
    }
};

class ButtonLNF : public juce::LookAndFeel_V4
{
public:
    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        const auto buttonSkin = juce::Drawable::createFromImageData(BinaryData::faderMovable_svg, BinaryData::faderMovable_svgSize);
        auto buttonArea = button.getLocalBounds();

        auto edge = 2;

        buttonArea.removeFromLeft (edge);
        buttonArea.removeFromTop (edge);
        
        auto offset = shouldDrawButtonAsDown ? -edge / 2 : -edge;
        buttonArea.translate (offset, offset);
        
        if (button.getToggleState())
        {
            buttonSkin->drawWithin(g, buttonArea.toFloat(), juce::RectanglePlacement::centred, 1.0f);
        }
        else
        {
            buttonSkin->drawWithin(g, buttonArea.toFloat(), juce::RectanglePlacement::centred, 0.7f);
        }
    
    }

};


//==============================================================================
/**
*/
class DeetzStortionAPVTSAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DeetzStortionAPVTSAudioProcessorEditor (DeetzStortionAPVTSAudioProcessor&);
    ~DeetzStortionAPVTSAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    //instansiating the background obj
    std::unique_ptr<juce::Drawable> background_image;
    
    //instansiating the slider obj
    OtherLookAndFeel sliderLookAndFeel;
    DistLNF distLNF;
    ButtonLNF buttonLNF;

    //Instansiating the sliders
    juce::Slider mDriveSlider;
    juce::Slider mDryWetSlider;
    juce::Slider mVolumeSlider;
    juce::Slider mDistortionType;

    juce::Slider mlowpassSlider;
    juce::Slider mhighpassSlider;
    
    juce::ToggleButton mMakeupGainToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> makeupGainAttachment;
    
    juce::HyperlinkButton mLearnMoreButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowpassSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highpassSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryWetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionTypeAttachment;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DeetzStortionAPVTSAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeetzStortionAPVTSAudioProcessorEditor)
};
