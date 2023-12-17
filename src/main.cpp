#include <stdio.h>
#include <tgbot/tgbot.h>
#include <vector>
#include "token.h"
#include "user.h"

void CreateKayboard(const std::vector<std::string> buttonStrings, TgBot::InlineKeyboardMarkup::Ptr& kb){
    for(auto iter: buttonStrings){
        std::vector<TgBot::InlineKeyboardButton::Ptr> row;
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->text = iter;
        button->callbackData = iter;
        row.push_back(button);
        kb->inlineKeyboard.push_back(row);
    }
}

int main() {
    TgBot::Bot bot(TOKEN);

    TgBot::InlineKeyboardMarkup::Ptr keyboardRegister(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardMarkup::Ptr selectDirections(new TgBot::InlineKeyboardMarkup);

    CreateKayboard({"Регистрация"}, keyboardRegister);
    CreateKayboard({
        "Медиа", "Дизайн", "Рабочка", "CММ", "Креаторка", "Фандрайзинг", "Волонтёрка", "Комитет", "Ютуб"
    }, selectDirections);



    bot.getEvents().onCommand("start", [&bot, &keyboardRegister](TgBot::Message::Ptr message){
        printf("User started: %s\n", message->chat->username.c_str());
        
        bot.getApi().sendMessage(message->chat->id, "Привет! Это бот проектного направления Студенческого совета РФиКТ!");
        bot.getApi().sendMessage(message->chat->id, "Выберете действие:", false, 0, keyboardRegister);
       // bot.getApi().deleteMessage(message->chat->id, message->messageId);
        
    });

    // bot.getEvents().onCommand("Регистрация", [&bot, &selectDirections](TgBot::Message::Ptr message){
    //     bot.getApi().sendMessage(message->chat->id, "Выбери свое направление: ", false, 0, selectDirections);
    // });

    bot.getEvents().onCallbackQuery([&bot, &selectDirections](TgBot::CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "Регистрация")) {
            bot.getApi().deleteMessage(query->message->chat->id, query->message->messageId);
            bot.getApi().deleteMessage(query->message->chat->id, query->message->messageId - 1);
            // bot.getApi().deleteMessage(query->message->chat->id, query->message->messageId - 2);
            std::string response = "Выбери свое направление";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, selectDirections, "Markdown");
        }
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}