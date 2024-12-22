from domain.examen import Examen
class RepositoryExamenFisier:
    def __init__(self,cale_fisier):
        self.__examene={}
        self.__cale_fisier=cale_fisier

    def __read_all_from_file(self):
        with open(self.__cale_fisier,'r') as f:
            self.__examene.clear()
            lines=f.readlines()
            for line in lines:
                line=line.strip()
                if line!='':
                    parti=line.split(',')
                    id=int(parti[0])
                    data=parti[1]
                    ora=parti[2]
                    materia=parti[3]
                    tip=parti[4]
                    examen=Examen(id,data,ora,materia,tip)
                    self.__examene[id]=examen

    def __write_all_to_file(self):
        with open(self.__cale_fisier,'w') as f:
            for id in self.__examene:
                f.write(str(self.__examene[id])+"\n")
    def add_examen(self,examen_add):
        self.__read_all_from_file()
        id=examen_add.get_id()
        materie=examen_add.get_materia()
        tip=examen_add.get_tip()
        if id in self.__examene:
            raise Exception("id existent")
        toate_examene=self.get_all()
        for examen in toate_examene:
            if examen.get_materia()==materie and examen.get_tip()==tip:
                raise Exception("nu se pot 2 examene la aceeasi materie de acelasi tip")
        self.__examene[id]=examen_add
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return [self.__examene[x] for x in self.__examene.keys()]
