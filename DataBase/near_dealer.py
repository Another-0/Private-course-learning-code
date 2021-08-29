import pymysql as sql


def find_dealer(address):
    address = address.replace(' ', '')
    select = """
    SELECT dealer,model,remain
    FROM dealers,remains
    WHERE dealers.sid=remains.sid
    AND dealers.address=
    """+'\'' + address + '\''
    db = sql.connect(host="localhost", user="car",
                     password="123456", database="cardb")
    cursor = db.cursor()
    try:
        cursor.execute(select)
        data = cursor.fetchall()
        if data == ():
            print("未查询到附近经销商！")
        else:
            print("       经销商       |      型号      |     库存\n")
            for i in data:
                dealer = i[0]
                model = i[1]
                remain = i[2]
                print('{: ^20}'.format(dealer), end='')
                print('{: ^16}'.format(model), end='')
                print('{: ^14}\n'.format(remain))
    except:
        print('输入有误！')
    db.close()


if __name__ == '__main__':
    print("{: ^45}".format('长城汽车附近经销商库存查询'))
    address = input("请输入你想查询的城市：")
    find_dealer(address)
