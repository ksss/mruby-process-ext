assert 'Process.uid' do
  assert_kind_of Fixnum, Process.uid
end

assert 'Process.gid' do
  assert_kind_of Fixnum, Process.gid
end

assert 'Process.euid' do
  assert_kind_of Fixnum, Process.euid
end

assert 'Process.egid' do
  assert_kind_of Fixnum, Process.egid
end

assert 'Process.uid=' do
  assert_equal Process.uid, Process.uid = Process.uid
end

assert 'Process::Sys.getuid' do
  assert_true Process.uid == Process::Sys.getuid
end

assert 'Process::Sys.getgid' do
  assert_true Process.gid == Process::Sys.getgid
end

assert 'Process::Sys.geteuid' do
  assert_true Process.euid == Process::Sys.geteuid
end

assert 'Process::Sys.getegid' do
  assert_true Process.egid == Process::Sys.getegid
end

assert 'Process::Sys.setuid' do
  begin
    assert_nil Process::Sys.setuid(Process.uid)
  rescue NotImplementedError
    skip 'This environment not have system call setuid(2)'
  end
end

assert 'Process::Sys.setruid' do
  begin
    assert_nil Process::Sys.setruid(Process.uid)
  rescue NotImplementedError
    skip 'This environment not have system call setruid(2)'
  end
end

assert 'Process::Sys.setreuid' do
  begin
    assert_nil Process::Sys.setreuid(Process.uid, -1)
  rescue NotImplementedError
    skip 'This environment not have system call setreuid(2)'
  end
end

assert 'Process::Sys.setresuid' do
  begin
    assert_nil Process::Sys.setresuid(Process.uid, -1, -1)
  rescue NotImplementedError
    skip 'This environment not have system call setresuid(2)'
  end
end
