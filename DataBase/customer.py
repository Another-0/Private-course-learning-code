import pymysql as sql
import os

db = sql.connect(host='localhost', user='custom',
                 password='123456', database='cardb')

while 1:
    print('\n1.显示所有经销商\n')
    print('2.查找经销商\n')
    print('3.退出\n')
    button = int(input(('输入标号执行选项：')))
    if button == 2:
        name = input('请输入经销商名称：').replace(' ', '')
        try:
            select = """
            SELECT dealer,address,model,price,remain
            FROM dealers,remains
            WHERE dealers.sid=remains.sid
            AND dealer=\'"""+name+'\''
            cursor = db.cursor()
            cursor.execute(select)
            data = cursor.fetchall()
            if data == ():
                print("\n该经销商不存在！")
            else:
                print("   经销商   |   地址   |  型号  |  价格(万元)  |  库存  \n")
                for i in data:
                    print('{: ^12}'.format(i[0]), end='')
                    print('{: ^10}'.format(i[1]), end='')
                    print('{: ^8}'.format(i[2]), end='')
                    print('{: ^14}'.format(i[3]), end='')
                    print('{: ^9}'.format(i[4]))
            input('\n按下回车键返回：')
            print('\n')
        except:
            print("输入有误")

    elif button == 1:
        try:
            cursor = db.cursor()
            select = """
            SELECT dealer,address
            FROM dealers
            """
            cursor.execute(select)
            data = cursor.fetchall()
            if data == ():
                print("无经销商！")
            else:
                print('\n经销商名称  |  地址')
                for i in data:
                    print('{: ^10}'.format(i[0]), end='')
                    print('{: ^10}'.format(i[1]))
            input('\n按下回车键返回：')
            print('\n')
        except:
            print("输入有误")
    elif button == 3:
        break
    else:
        print('\n输入错误，请重新输入！')
        input('按回车键重新输入：')
    os.system('cls')
    continue
db.close()
