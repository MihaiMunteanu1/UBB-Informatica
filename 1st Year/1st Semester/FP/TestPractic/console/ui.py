class UI:
    def __init__(self,srv_tractor):
        self.__srv_tractor=srv_tractor
        self.__lista_de_tiparit=[]
        self.__commands={
            "add_tractor":self.__ui_add_tractor,
            "sterge_tractor":self.__ui_sterge_tractor,
            "undo":self.__ui_undo,
            "filtrare_tractoare":self.__ui_filtrare_tractoare,
        }
    def __ui_filtrare_tractoare(self,params):
        """
        Functie care primeste ca parametrii conditiile dupa care dorim sa filtram tractoarele si
        le afiseaza dupa
        :param params:
        :return:
        """
        if len(params)!=2 and len(params)!=1:
            print("numar parametrii invalid")
            return
        if len(params)==2:
            try:
                text=params[0]
                numar=int(params[1])
            except ValueError:
                raise Exception("parametrii invalizi")
        if len(params)==1:
            try:
                numar=int(params[0])
            except ValueError:
                raise Exception("parametrii invalizi")
            text=''
        final_result=self.__srv_tractor.filtrare_tractoare(text,numar)
        print(f"filtru: text={text}, numar={numar}")
        self.__lista_de_tiparit=final_result
        if final_result!=[]:
            for result in final_result:
                print(result)
    def __ui_undo(self,params):
        """
        Functie care apeleaza functia de undo din service
        :param params:
        :return:
        """
        if len(params)!=0:
            print("numar parametrii invalid")
            return
        self.__srv_tractor.undo()
        print("undo realizat cu succes")
        for lista in self.__lista_de_tiparit:
            print(lista)

    def __ui_sterge_tractor(self,params):
        """
        Functie care verifica daca cifra aleasa de noi e numar intreg si apelaza
        service pentru a continua cu stergerea tractoarelor
        :param params:
        :return:
        """
        if len(params)!=1:
            print("numar parametrii invalid")
            return
        try:
            cifra=int(params[0])
        except ValueError:
            raise Exception("parametrii invalizi")
        self.__srv_tractor.sterge_tractor(cifra)
        for lista in self.__lista_de_tiparit:
            print(lista)
    def __ui_add_tractor(self,params):
        """
        Functie care verifica daca parametrii sunt buni si trimite la service pentru
        adaugarea unui nou tractor
        :param params:
        :return:
        """
        if len(params)!=5:
            print("numar parametrii invalid")
            return
        try:
            id=int(params[0])
            denumire=params[1]
            pret=int(params[2])
            model=params[3]
            data=params[4]
        except ValueError:
            raise Exception("parametrii invalizi")
        self.__srv_tractor.add_tractor(id,denumire,pret,model,data)
        print("tractor adaugat cu succes")
        for lista in self.__lista_de_tiparit:
            print(lista)

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