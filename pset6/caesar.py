import cs50
import sys

def main():
    
    #checa que solo des un numero para el giro
    if len(sys.argv) != 2:
        print("Wroooong")
        return 1;
    k = int(sys.argv[1])%26
    p = input("Enter plaintext:")
    
    p_array = list(p)
    p_ASCII = []
    c = []
    #converts the string to numbers and then adds k
    for i in p_array:
        j=ord(i)
        #convierte mayúsculas
        if ((j < 91) and (j > 64)):
            if (j+k)>90:
                p_ASCII.append(j+k-26)
            else:
                p_ASCII.append(j+k)
            
        #convierte minúsculas
        elif ((j < 123) and (j > 96)):
            if (j+k)>122:
                p_ASCII.append(j+k-26)
            else: 
                p_ASCII.append(j+k)
        #no mueve caracteres especiales
        else:
            p_ASCII.append(j)
            
    #convert ASCII to char
    for l in p_ASCII:
        c.append(chr(l))
    
    #convert array to string    
    c2= ''.join(c)   
    print("list = {}".format(c2))
    return 0

if __name__ == "__main__":
    main()