import random
from storage import Storage
from filegenerator import generate_products, generate_users


class Query(Storage):
    storage = 'S3'

    def __init__(self, look_up, data=None):
        self.data = data
        self.look_up = look_up

    def get(self):
        products_stored = self.read_file(self.look_up)
        results = [
            {
                'product_id': item['product_id'],
                'product_name': products_stored[str(item['product_id'])]['name'],
                'qty': item['qty'],
                'cost_total': (item['qty'] * products_stored[str(item['product_id'])]['value'])
            }
            for idx, item in self.data.items()
        ]

        return results

    def update_data(self):
        self.write_file(self.data)


# generate random data, this is just a database repo mock
if not generate_products():
    exit(0)
if not generate_users():
    exit(0)

# Pseudo table names
products_storage = 'products'
user_storage = 'users'

# user input mock
user_transactions = {'A' + str(index): {'qty': random.randint(0, 10), 'product_id': random.randint(1, 99)}
                     for index in range(0, 10)}

products = Query(data=user_transactions, look_up=products_storage)
results = products.get()

if (len(results) == len(user_transactions)):
    print("All transactions where populated: ", len(results), results)
else:
    print("Error, products incorrect: ", len(results), results)
#
# product_name = Structure(file_input=products_path)
# print(product_name.data)
# print(product_name.storage)
