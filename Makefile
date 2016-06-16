
miniature-eureka: racelauncher.c
	$(CC) $< -o $@

clean:
	rm -f miniature-eureka
	rm -f *.o
