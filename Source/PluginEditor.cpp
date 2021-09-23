/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DeetzStortionAPVTSAudioProcessorEditor::DeetzStortionAPVTSAudioProcessorEditor (DeetzStortionAPVTSAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //background properties
    background_image = juce::Drawable::createFromImageData(BinaryData::background_image2_svg, BinaryData::background_image2_svgSize);
    addAndMakeVisible(*background_image);

    //Highpass
    mhighpassSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mhighpassSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 25);
    mhighpassSlider.setSkewFactor(15.0f,true);
    mhighpassSlider.setLookAndFeel(&sliderLookAndFeel);
    mhighpassSlider.setRotaryParameters(juce::degreesToRadians(0.f), juce::degreesToRadians(220.f), true);
    mhighpassSlider.setSkewFactor(0.5, false);
    addAndMakeVisible(mhighpassSlider);
    //Lowpass
    mlowpassSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mlowpassSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 25);
    mlowpassSlider.setTextValueSuffix("Hz");
    mlowpassSlider.setLookAndFeel(&sliderLookAndFeel);
    mlowpassSlider.setRotaryParameters(juce::degreesToRadians(0.f), juce::degreesToRadians(220.f), true);
    mhighpassSlider.setSkewFactor(0.2, false);
    addAndMakeVisible(mlowpassSlider);

    //Drive
    mDriveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDriveSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 25);
    mDriveSlider.setLookAndFeel(&sliderLookAndFeel);
    mDriveSlider.setRotaryParameters(juce::degreesToRadians(0.f), juce::degreesToRadians(220.f), true);
    mDriveSlider.setSkewFactor(0.5, false);
    addAndMakeVisible(mDriveSlider);


    //DistortionType
    mDistortionType.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mDistortionType.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,false,100,50);
    mDistortionType.setLookAndFeel(&distLNF);
    addAndMakeVisible(mDistortionType);

    //DryWet
    mDryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDryWetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 25);
    mDryWetSlider.setTextValueSuffix("%");
    mDryWetSlider.setLookAndFeel(&sliderLookAndFeel);
    mDryWetSlider.setRotaryParameters(juce::degreesToRadians(0.f), juce::degreesToRadians(220.f), true);
    addAndMakeVisible(mDryWetSlider);

    //Volume
    mVolumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mVolumeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 25);
    mVolumeSlider.setTextValueSuffix("dB");
    mVolumeSlider.setLookAndFeel(&sliderLookAndFeel);
    mVolumeSlider.setRotaryParameters(juce::degreesToRadians(0.f), juce::degreesToRadians(220.f), true);
    addAndMakeVisible(mVolumeSlider);

    //HyperLink Button
    mLearnMoreButton.setURL({ "http://www.juce.com" });
    addAndMakeVisible(mLearnMoreButton);


    //Connecting attachments to components
    highpassSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HIGHPASSCUTOFF", mhighpassSlider);
    lowpassSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LOWPASSCUTOFF", mlowpassSlider);
    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRIVE", mDriveSlider);
    dryWetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRYWET", mDryWetSlider);
    volumeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VOLUME", mVolumeSlider);
    distortionTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DISTORTIONTYPE", mDistortionType);
    setSize(900, 450);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.



}


DeetzStortionAPVTSAudioProcessorEditor::~DeetzStortionAPVTSAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void DeetzStortionAPVTSAudioProcessorEditor::paint (juce::Graphics& g)
{
/*
    const auto svg = juce::Drawable::createFromImageData(BinaryData::deetzStortion_GUI_svg, BinaryData::deetzStortion_GUI_svgSize);
    svg->draw(g, 1.0);
    */
}

void DeetzStortionAPVTSAudioProcessorEditor::resized()
{
    background_image->setBounds(-1,-12,900,450);
    mhighpassSlider.setBounds(60-2, 200, 100,100);
    mlowpassSlider.setBounds(160-1, 200, 100, 100);
    mDriveSlider.setBounds(340, 200, 100, 100);
    mLearnMoreButton.setBounds(800, 420, 200, 30);
    mDryWetSlider.setBounds(552,200, 100, 100);
    mVolumeSlider.setBounds(755, 200, 100, 100);
    mDistortionType.setBounds(312, 173, 126, 20);

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}