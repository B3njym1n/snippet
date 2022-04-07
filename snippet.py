def main():
    for i in range(10):
        if (i < 5):
            pass
        else:
            print("counted to {}".format(i))
            break
        print("while loop body runs here")

if __name__ == '__main__':
    main()
