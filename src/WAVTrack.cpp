#include "WAVTrack.h"
#include <iostream>

WAVTrack::WAVTrack(const std::string& title, const std::vector<std::string>& artists, 
                   int duration, int bpm, int sample_rate, int bit_depth)
    : AudioTrack(title, artists, duration, bpm), sample_rate(sample_rate), bit_depth(bit_depth) {

    std::cout << "WAVTrack created: " << sample_rate << "Hz/" << bit_depth << "bit" << std::endl;
}

// ========== TODO: STUDENTS IMPLEMENT THESE VIRTUAL FUNCTIONS ==========

void WAVTrack::load() {
    std::cout << "[WAVTrack::load] Loading WAV: \"" << title
              << "\" at " << sample_rate << "Hz/" << bit_depth 
              << "bit (uncompressed)...\n";
    
    // Calculate estimated file size
    long long size = duration_seconds * sample_rate * (bit_depth / 8) * 2;
    
    std::cout << "  → Estimated file size: " << size << " bytes\n";
    std::cout << "  → Fast loading due to uncompressed format.\n";
}

void WAVTrack::analyze_beatgrid() {
    std::cout << "[WAVTrack::analyze_beatgrid] Analyzing beat grid for: \"" << title << "\"\n";
    // Calculate estimated beats
    double beats = (duration_seconds / 60.0) * bpm;

    std::cout << "  → Estimated beats: " << int(beats) << "  → Precision factor: 1.0 (uncompressed audio)" << "\n";
}

double WAVTrack::get_quality_score() const {
    //Start with base score of 70
    double score = 70.0;

    // Increase score based on sample rate and bit depth
    if (sample_rate >= 96000) {
        score += 15.0;
    }
    else if (sample_rate >= 44100) {
        score += 10.0;
    }
    if (bit_depth >= 24) {
        score += 15.0;
    }
    else if (bit_depth >= 16) {
        score += 10.0;
    }

    // Clamp score between 0 and 100
    if (score > 100.0) score = 100.0;

    return score;
}

PointerWrapper<AudioTrack> WAVTrack::clone() const {
    // create and return a new WAVTrack copy
    return PointerWrapper<AudioTrack>(new WAVTrack(*this)); 
}
