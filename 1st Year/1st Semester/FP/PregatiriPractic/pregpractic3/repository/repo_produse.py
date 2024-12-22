from domain.produs import Produs
class FileRepoProduse:
    def __init__(self,cale_fisier):
        self.__produs={}
        self.__undo=[]
        self.__cale_fisier=cale_fisier

    def __read_all_from_file(self):
        with open(self.__cale_fisier,'r') as f:
            self.__produs.clear()
            lines=f.readlines()
            for line in lines:
                line=line.strip()
                if line!=' ':
                    parti=line.split(',')
                    id=int(parti[0])
                    denumire=parti[1]
                    pret=int(parti[2])
                    produs=Produs(id,denumire,pret)
                    self.__produs[id]=produs

    def __write_all_to_file(self):
        with open(self.__cale_fisier,'w') as f:
            for id in self.__produs.keys():
                f.write(str(self.__produs[id])+'\n')

    def add_produs(self,produs):
        self.__read_all_from_file()
        id_produs=produs.get_id()
        if id_produs in self.__produs:
            raise Exception("id existent")
        else:
            self.__produs[id_produs]=produs
        self.__write_all_to_file()

    def filtrare(self,text,numar):
        result=[]
        if numar!=-1 and text!='':
            for produs in self.get_all():
                pret=produs.get_pret()
                if pret<numar:
                    denumire=produs.get_denumire()
                    if text in denumire:
                        result.append(produs)
        if numar==-1 and text!='':
            for produs in self.get_all():
                denumire=produs.get_denumire()
                if text in denumire:
                    result.append(produs)
        if numar!=-1 and text=='':
            for produs in self.get_all():
                pret=produs.get_pret()
                if pret<numar:
                    result.append(produs)
        return result
    def filtrare2(self,numar):
        result=[]
        if numar!=-1:
            for produs in self.get_all():
                pret=produs.get_pret()
                if pret<numar:
                    result.append(produs)
        if numar==-1:
            return result
        return result

    def undo(self):
        self.__read_all_from_file()
        self.__produs.clear()
        self.__produs=self.__undo.copy()
        self.__write_all_to_file()

    def sterge_produse(self,cifra):
        self.__read_all_from_file()
        ok=int(0)
        toate_produse=self.get_all()
        self.__undo=self.__produs.copy()
        for produs in toate_produse:
            id=produs.get_id()
            cop_id=id
            while cop_id>0:
                c=cop_id%10
                if c==cifra:
                    del self.__produs[id]
                    ok=1
                    cop_id=0
                else:
                    cop_id=cop_id/10
        if ok==1:
            print("au fost sterse produse")
        else:
            print("nu exista produse al caror id contine aceasta cifra")
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return [self.__produs[x] for x in self.__produs.keys()]