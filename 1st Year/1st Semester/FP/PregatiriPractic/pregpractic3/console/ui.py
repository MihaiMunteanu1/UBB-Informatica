class UI:
    def __init__(self,srv_produse):
        self.__srv_produse=srv_produse
        self.__commands={
            "add_produs":self.__ui_add_produs,
            "sterge":self.__ui_sterge_produse,
            "filtrare":self.__ui_filtrare,
            "undo":self.__ui_undo,
        }
    def __ui_undo(self,params):
        if len(params)!=0:
            print("numar parametrii invalid")
            return
        self.__srv_produse.undo()
    def __ui_filtrare(self,params):
        if len(params)!=2 and len(params)!=1:
            print("numar parametrii invalid")
            return
        if len(params)==2:
            try:
                text=params[0]
                numar=int(params[1])
            except ValueError:
                raise Exception("parametrii invalizi")
            rezultat=self.__srv_produse.filtrare(text,numar)
            for produs in rezultat:
                print(produs)
        if len(params)==1:
            try:
                numar=int(params[0])
            except ValueError:
                raise Exception("parametrii invalizi")
            rezultat=self.__srv_produse.filtrare2(numar)
            for produs in rezultat:
                print(produs)

    def __ui_sterge_produse(self,params):
        if len(params)!=1:
            print("numar parametrii invalid")
            return
        try:
            cifra=int(params[0])
        except ValueError:
            raise Exception("parametrii invalizi")
        self.__srv_produse.sterge_produse(cifra)
    def __ui_add_produs(self,params):
        if len(params)!=3:
            print("numar parametrii invalid")
            return
        try:
            id=int(params[0])
            denumire=params[1]
            pret=int(params[2])
        except ValueError:
            raise Exception("parametrii invalizi")
        self.__srv_produse.add_produs(id,denumire,pret)
        print("produs adaugat cu succes")
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