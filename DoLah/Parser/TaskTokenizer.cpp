#include "TaskTokenizer.h"


namespace DoLah {
    std::vector<std::string> TaskTokenizer::DEADLINE_INDICATOR = { "on", "by" };
    std::string TaskTokenizer::SCHEDULE_INDICATOR = "from";
    std::vector<std::string> TaskTokenizer::SCHEDULE_SEPARATOR = { "to", "until" };
    std::string TaskTokenizer::tag = "#";

    TaskTokenizer::TaskTokenizer() {
    }


    TaskTokenizer::~TaskTokenizer() {
    }

    std::vector<std::string> TaskTokenizer::findTags(std::vector<std::string> lineArr) {
        std::vector<std::string> tags;
        std::vector<std::string> moretags;

        for (size_t i = 0; i < lineArr.size(); i++) {
            moretags = ParserLibrary::explode(lineArr.at(i), tag);
            tags.insert(tags.begin(), moretags.begin() + 1, moretags.end());
        }

        for (size_t i = 0; i < tags.size(); i++) {
            tags.at(i) = ParserLibrary::tolowercase(tags.at(i));
        }

        tags = ParserLibrary::stringVectorUnique(tags);

        return tags;
    }

    std::string TaskTokenizer::findDescription(std::vector<std::string> lineArr) {
        return ParserLibrary::implode(lineArr, " ");
    }

    std::vector<std::tm> TaskTokenizer::findAndRemoveDate(std::vector<std::string> &lineArr) {
        TaskTokenizer ct;
        std::vector<std::tm> output;

        try {
            for (size_t i = lineArr.size() - 1; i > 0; i--) {
                if (ParserLibrary::inStringArray(DEADLINE_INDICATOR, ParserLibrary::tolowercase(lineArr.at(i)))) {
                    std::vector<std::string> subVec(lineArr.begin() + i + 1, lineArr.end());

                    std::tm time = DateTimeParser::toDateFormat(subVec);

                    output.push_back(time);
                    lineArr.erase(lineArr.begin() + i, lineArr.end());
                    return output;
                } else if (SCHEDULE_INDICATOR == ParserLibrary::tolowercase(lineArr.at(i))) {
                    std::vector<std::string> subVec(lineArr.begin() + i + 1, lineArr.end());
                    for (size_t j = 0; j < subVec.size(); j++) {
                        if (ParserLibrary::inStringArray(SCHEDULE_SEPARATOR, ParserLibrary::tolowercase(subVec.at(j)))) {
                            std::vector<std::string> startDateArr(subVec.begin(), subVec.begin() + j);
                            std::vector<std::string> endDateArr(subVec.begin() + j + 1, subVec.end());

                            std::tm startdate = DateTimeParser::toDateFormat(startDateArr);
                            std::tm enddate = DateTimeParser::toDateFormat(endDateArr);

                            output.push_back(startdate);
                            output.push_back(enddate);
                            lineArr.erase(lineArr.begin() + i, lineArr.end());
                            return output;
                        }
                    }
                }
            }
        } catch (std::invalid_argument e) {
            // do nothing
        }

        return output;
    }
}
