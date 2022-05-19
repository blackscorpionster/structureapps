from os import remove
import json
import random


def generate_products():
    try:
        file_path = 'products.json'
        words_file = open('ipsum.txt', 'r')
        words = words_file.read().split(' ')
        n_words = len(words)

        file = open(file=file_path, mode='x', encoding="utf-8")
        data = {
            idx: {'name': item, 'value': random.randrange(10, 500), 'id': idx}
            for idx, item in enumerate(random.sample(words, 100 if n_words > 100 else n_words))
        }
        json.dump(data, file, indent=True)
        file.close()

        print("File {nme} created successfully.".format(nme=file_path))
        return True
    except FileExistsError:
        return True
    except Exception as e:
        remove(file_path)
        raise e


def generate_users():
    file_path = 'users.json'

    words_handler = open('ipsum.txt', 'r')
    words = words_handler.read().split(' ')
    words_handler.close()

    try:
        users_file = open(file_path, 'x')
        users = {
            index: {'id': index, 'first_name': us['f_name'], 'last_name': us['l_name']} for index, us in
            enumerate(
                [{'f_name': random.sample(words, 1).pop(), 'l_name': random.sample(words, 1).pop()} for index in range(0, 100)]
            )
        }

        json.dump(users, users_file, indent=True)
        users_file.close()

        print("File {nme} created successfully.".format(nme=file_path))
        return True
    except FileExistsError:
        return True
    except Exception as e:
        remove(file_path)
        raise e
