import requests as requests

token = '1038545779:AAEKIw4oF7AfxeQPTpaZZgYJHtKu90uwDU8'
url = 'https://api.telegram.org/bot'+ token + '/'

def get_chat_id(update):
    chat_id = update["message"]["chat"]["id"]
    return chat_id

def get_message(update):
    message = update['message']["text"]
    return message

def last_update(req):
    response = requests.get(req + "getUpdates")
    response = response.json()
    result = response["result"]
    total_update = len(result) - 1
    return result[total_update]
    return response

def send_message(chat_id, text):
    params = {"chat_id": chat_id, "text":text}
    response = requests.post(url + "sendMessage",  data = params)
    return response

def main():
    
    update_id = last_update(url)["update_id"]
    print(update_id)
    
    while True:
        update = last_update(url)
        if update_id == update["update_id"]:
            if get_message(update).lower() == 'hi' or get_message(update).lower() == 'hello':
                send_message(get_chat_id(update), 'Welcome my bot')
            else:
                send_message(get_chat_id(update), 'Não consigo compreender')

            update_id +=  1


main()

