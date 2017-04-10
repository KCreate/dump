prot = LibC::PROT_READ | LibC::PROT_WRITE
flags = LibC::MAP_SHARED | LibC::MAP_ANON
memory_size = 1024

shared_memory = LibC.mmap(nil, memory_size, prot, flags, -1, 0)
bytes = Bytes.new Pointer(UInt8).new(shared_memory.address), memory_size
io = IO::Memory.new bytes

Process.fork do |child|
  io.puts "hello world"
  puts "wrote to shared memory"
end

sleep 5
puts bytes.hexdump

LibC.munmap(shared_memory, memory_size)
