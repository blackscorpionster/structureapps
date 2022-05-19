import json


class Storage:
    storage_type = 'json'

    def read_file(self, file_input):
        storage_file = '{file}.{ext}'.format(file=file_input, ext=self.storage_type)
        file_handler = open(storage_file, 'r')
        data = json.load(file_handler)
        file_handler.close()
        return data

    def write_file(self, data=None):
        pass
