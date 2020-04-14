

# finds the esp module if arduino isn't
esp:
	esptool.py read_flash_status

# after generating, remove src/mta from the front of files in *.pb.c
# this command is in place of:
# protoc --proto_path=src/proto --nanopb_out=src/mta src/proto/*.proto
# gen-proto:
# 	python generator/nanopb_generator.py src/mta/gtfs-realtime.proto
