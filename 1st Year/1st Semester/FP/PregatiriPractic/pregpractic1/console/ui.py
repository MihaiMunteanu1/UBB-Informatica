class UI:
    def __init__(self,srv_emisiune):
        self.__srv_emisiune=srv_emisiune
        self.__lista_blocata=[]
        self.__commands={
            "print":self.__ui_print,
            "sterge":self.__ui_sterge,
            "update":self.__ui_update,
            "ore":self.__ui_ore,
            "lista":self.__ui_lista,
        }
    def __ui_lista(self,params):
        if len(params)==0:
            self.__lista_blocata=''
        else:
            for i in range(len(params)):
                self.__lista_blocata.append(params[i])

    def __ui_ore(self,params):
        if len(params)!=2:
            print("nr params invalid")
            return
        try:
            ora_inceput=int(params[0])
            ora_sfarsit=int(params[1])
        except ValueError:
            raise Exception("parametrii invalizi")
        emisiuni=self.__srv_emisiune.ore(ora_inceput,ora_sfarsit)
        for emisiune in emisiuni:
            print(emisiune)
    def __ui_update(self,params):
        if len(params)!=4:
            print("nr params invalid")
            return
        try:
            nume=params[0]
            tip=params[1]
            durata=int(params[2])
            descriere=params[3]
        except ValueError:
            raise Exception("parametrii invalizi")
        if tip in self.__lista_blocata:
            print("tipul este blocat")
        else:
            self.__srv_emisiune.update(nume,tip,durata,descriere)
            print("actualizare cu succes")
    def __ui_sterge(self,params):
        if len(params)!=2:
            print("nr params invalid")
            return
        try:
            nume=params[0]
            tip=params[1]
        except ValueError:
            raise Exception("parametrii invalizi")
        if tip in self.__lista_blocata:
            print("tipul este blocat")
        else:
            self.__srv_emisiune.sterge(nume,tip)
            print("stergere efectuata cu succes")
    def __ui_print(self,params):
        if len(params)!=0:
            print("nr params invalid")
            return
        emisiuni=self.__srv_emisiune.get_all()
        for emisiune in emisiuni:
            print(emisiune)

    def run(self):
        while True:
            cmd=input(">>>")
            cmd=cmd.strip()
            if cmd=='exit':
                return
            parti=cmd.split(' ')
            nume=parti[0]
            params=parti[1:]
            if nume in self.__commands:
                try:
                    self.__commands[nume](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida")