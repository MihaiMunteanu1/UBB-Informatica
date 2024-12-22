class UI:
    def __init__(self,srv_piese):
        self.__srv_piese=srv_piese
        self.__commands={
            "add":self.__ui_add_piesa,
            "print":self.__ui_print,
            "modifica":self.__ui_modifica,
            "random":self.__ui_random,
            "export":self.__ui_export,
        }
    def __ui_export(self,params):
        if len(params) != 1:
            print("nr parametrii invalid")
            return
        try:
            nume_fisier=params[0]
        except ValueError:
            raise Exception("parametrii invalizi")
        result=self.__srv_piese.export()
        with open(nume_fisier,'w') as f:
            for piesa in result:
                f.write(str(piesa)+'\n')
    def __ui_random(self,params):
        if len(params) != 1:
            print("nr parametrii invalid")
            return
        try:
            numere=int(params[0])
        except ValueError:
            raise Exception("parametrii invalizi")
        if numere<1:
            raise Exception("parametrii invalizi")
        piese_generate=self.__srv_piese.random(numere)
        for piesa in piese_generate:
            print(piesa)
    def __ui_modifica(self,params):
        if len(params)!=4:
            print("nr parametrii invalid")
            return
        try:
            titlu = params[0]
            regizor = params[1]
            new_gen = params[2]
            new_durata = int(params[3])
        except ValueError:
            raise Exception("parametrii invalizi")
        self.__srv_piese.modifica(titlu,regizor,new_gen,new_durata)
        print("piesa modificata cu succes")
    def __ui_print(self,params):
        if len(params)!=0:
            print("nr parametrii invalid")
            return
        piese=self.__srv_piese.get_all()
        for piesa in piese:
            print(piesa)
    def __ui_add_piesa(self,params):
        if len(params)!=5:
            print("nr parametrii invalid")
            return
        try:
            id=int(params[0])
            titlu = params[1]
            regizor = params[2]
            gen = params[3]
            durata = int(params[4])
        except ValueError:
            raise Exception("parametrii invalizi")
        self.__srv_piese.add_piesa(id,titlu,regizor,gen,durata)
        print("piesa adaugata cu succes")
    def run(self):
        while True:
            cmd=input(">>>")
            cmd=cmd.strip()
            if cmd=='exit':
                return
            parti=cmd.split(' ')
            nume_comanda=parti[0]
            params=parti[1:]
            if nume_comanda in self.__commands:
                try:
                    self.__commands[nume_comanda](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida")