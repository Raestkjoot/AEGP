#include "TestLevelGeneration.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

void TestLevelGeneration::GenerateLevel() {
    std::ostringstream ss;

    ss << "{"; // {
    ss << "\"Systems\": ["
        << "\"AudioManagerSystem\", "
        << "\"MoveSystem\", "
        << "\"PlayerCollisionSystem\", "
        << "\"CameraFollowSystem\", "
        << "\"ClearRenderer\", "
        << "\"ClearUI\", "
        << "\"SpriteRenderer\", "
        << "\"TimingsSystem\""
        << "], ";

    ss << "\"Entities\": ["; // e[

    ss << "{ \"Name\": \"Player\",";
    ss << " \"Components\": [";
    ss << "{ \"Name\": \"Transform\", "
        << "\"Arguments\": {"
        << " \"Position\": [ 0.4, 8.0 ] "
        << "}},";
    ss << "{ \"Name\": \"Sprite\", "
        << "\"Arguments\": {"
        << " \"Name\": \"DefaultSquare\" "
        << "}},";
    ss << "{ \"Name\": \"AABB\", "
        << "\"Arguments\": {"
        << " \"Size\": [ 0.15, 0.35 ] "
        << "}},";
    ss << "{ \"Name\": \"PlayerController\", "
        << "\"Arguments\": {"
        << "}},";
    ss << "{ \"Name\": \"Collider_Dynamic\", "
        << "\"Arguments\": {"
        << "}}";
    ss  << "]},";

    ss << "{ \"Name\": \"Camera\",";
    ss << " \"Components\": [";
    ss << "{ \"Name\": \"Camera2D\", "
        << "\"Arguments\": {"
        << "}}";
    ss  << "]},";

    ss << "{ \"Name\": \"Floor\",";
    ss << " \"Components\": [";
    ss << "{ \"Name\": \"Transform\", "
        << "\"Arguments\": {"
        << " \"Position\": [ 0.0, -4.5 ], "
        << " \"Scale\": [ 12.0, 6.0 ] "
        << "}},";
    ss << "{ \"Name\": \"Sprite\", "
        << "\"Arguments\": {"
        << " \"Name\": \"DefaultSquare\" "
        << "}},";
    ss << "{ \"Name\": \"AABB\", "
        << "\"Arguments\": {"
        << " \"Size\": [ 6.0, 3.0 ] "
        << "}},";
    ss << "{ \"Name\": \"Collider_Static\", "
        << "\"Arguments\": {"
        << "}}";
    ss << "]},";

    for (int i = 0;; ++i) {
        float xPos = std::floor(i / _boxesPerRow) * _distance.x;
        float yPos = std::fmod(i, _boxesPerRow) * _distance.y;

        ss << "{ \"Name\": \"Box" << i << "\",";
        ss << " \"Components\": [";
        ss << "{ \"Name\": \"Transform\", "
            << "\"Arguments\": {"
            << " \"Position\": [ " << xPos << ", " << yPos << " ], "
            << " \"Scale\": [ " << _scale << ", " << _scale << " ] "
            << "}},";
        ss << "{ \"Name\": \"Sprite\", "
            << "\"Arguments\": {"
            << " \"Name\": \"DefaultSquare\" "
            << "}},";
        ss << "{ \"Name\": \"AABB\", " // Comment this component out to disable collision
            << "\"Arguments\": {"
            << " \"Size\": [ " << _scale / 2 << ", " << _scale / 2 << " ] "
            << "}},";
        ss << "{ \"Name\": \"Collider_Static\", "
            << "\"Arguments\": {"
            << "}}";
        ss << "]}";



        if (i < _numOfBoxesToSpawn) {
            ss << ",";
        } else {
            break;
        }
    }

    ss << "]"; // e]
    ss << "}"; // }

    std::string str = ss.str();

    nlohmann::json tmp = nlohmann::json::parse(str);
	std::ofstream o("output.json");
	o << tmp.dump(4);
}