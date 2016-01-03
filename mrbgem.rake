require 'mkmf'
require 'rake/clean'

# patch for old mkmf bug
if Gem::Version.create(RUBY_VERSION) <= Gem::Version.create('1.9.3')
  def try_link(src, opt = '', *opts, &b)
    try_link0(src, opt, *opts, &b)
  ensure
    rm_f ['conftest*', 'c0x32*']
  end
end
# patch end

dir = File.dirname(__FILE__)
extconf = "#{dir}/src/extconf.h"

file extconf => [__FILE__, "#{dir}/src/process.c"] do |t|
  File.unlink(t.name) if File.exist?(t.name)

  # TODO
  # if open this block
  # raise error: redefinition of 'struct timespec'
  # in windows
  if RUBY_PLATFORM !~ /mingw|mswin/
    have_func 'setresuid'
    have_func 'setreuid'
    have_func 'setruid'
    have_func 'setuid'
  end

  create_header t.name
end

CLOBBER << extconf

MRuby::Gem::Specification.new('mruby-process-ext') do |spec|
  spec.license = 'MIT'
  spec.author  = 'ksss <co000ri@gmail.com>'

  Rake::Task[extconf].invoke
end
