import pymysql as sql
pw = input('请输入您的MySQL管理员用户（root）密码：')
while True:
    if pw == 'exit':
        exit(1)
    try:
        db = sql.connect(host="localhost", user="root",
                         password=pw, database="cardb")
        break
    except:
        print('密码错误！请重新输入\n')
        pw = input('输入exit退出：')

print('成功连接！输入exit断开连接\n')


while True:
    cursor = db.cursor()
    query = input("代码输入>>")
    if query == 'exit':
        break
    else:
        while query[-1] != ';':
            t = input('>>')
            query = query+t
        try:
            cursor.execute(query)
            if query[0:6] != 'select' and query[0:6] != 'SELECT':
                db.commit()
            else:
                name = cursor.description
                for k in name:
                    print(k[0], end='  |')
                print('\n')
                data = cursor.fetchall()
                for i in data:
                    for j in i:
                        print(j, end='  |')
                    print('\n')
        except:
            print('语句错误！')
            db.rollback()

db.close()
