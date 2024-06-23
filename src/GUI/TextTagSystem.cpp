#include "stdafx.h"
#include "TextTagSystem.h"

/* PRIVATE FUNCTIONS ============================================================================================ */

void TextTagSystem::initFonts(const std::string font_path)
{
    if (!font.loadFromFile(font_path))
        ErrorHandler::throwErr("TEXTTAGSYSTEM::TEXTTAGSYSTEM::ERR_LOADING_FONT: " + font_path);
}

void TextTagSystem::initVariables()
{
}

void TextTagSystem::initTagTemplates()
{
    tagTemplates[DEFAULT_TAG] = new TextTag(0.f, 0.f,
                                            0, -1,
                                            0.f, 10.f,
                                            500.f,
                                            sf::Color::White,
                                            gui::calc_char_size(vm, 150),
                                            "", font);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

TextTagSystem::TextTagSystem(const std::string font_path, sf::VideoMode &vm)
    : vm(vm)
{
    initFonts(font_path);
    initVariables();
    initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
    for (auto tag : tags)
        delete tag;

    for (auto &it : tagTemplates)
        delete it.second;
}

/* FUNCTIONS ====================================================================================================== */

void TextTagSystem::update(const float &dt)
{
    for (auto tag : tags)
    {
        tag->update(dt);

        // TODO: find and optimal solution.
        if (tag->hasExceededLifetime())
        {
            removeTag(tag);
            break;
        }
    }
}

void TextTagSystem::render(sf::RenderTarget &target)
{
    for (auto tag : tags)
        tag->render(target);
}

void TextTagSystem::addTag(const TextTagType type, const float x, const float y, const std::string string)
{
    tags.push_back(new TextTag(*tagTemplates[type]));
    tags.back()->setString(string);
    tags.back()->setPosition(x, y);
}

void TextTagSystem::removeTag(TextTag *tag)
{
    auto tagIt = std::find(tags.begin(), tags.end(), tag);

    if (tagIt != tags.end())
        tags.erase(tagIt);
    else
        ErrorHandler::throwErr("TEXTTAGSYSTEM::REMOVETAG::ERR_TAG_NOT_FOUND");
}